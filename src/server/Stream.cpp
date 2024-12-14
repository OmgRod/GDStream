#include "Stream.hpp"
#include "config.hpp"
#include <Geode/Geode.hpp>
#include <ffmpeg/libavformat/avformat.h>
#include <ffmpeg/libavcodec/avcodec.h>
#include <ffmpeg/libavutil/avutil.h>
#include <ffmpeg/libavutil/opt.h>
#include <ffmpeg/libswscale/swscale.h>

using namespace geode::prelude;

bool Stream::init(int accID, const std::string& streamName) {
    std::string endpoint = ServerConfig::get()->m_serverEndpoint;
    log::debug("Initializing Stream: Account ID = {}, Stream Name = {}, Endpoint = {}", accID, streamName, endpoint);
    return true;
}

bool Stream::startRTMPStream(const std::string& streamName) {
    const std::string endpoint = ServerConfig::get()->m_serverEndpoint;
    const std::string rtmpURL = "rtmp://" + endpoint + "/live/" + streamName;

    log::info("Starting RTMP Stream: {}", rtmpURL);

    AVFormatContext* formatContext = nullptr;
    AVStream* videoStream = nullptr;

    // Register all formats and codecs
    av_register_all();
    avformat_network_init();

    // Allocate the format context
    if (avformat_alloc_output_context2(&formatContext, nullptr, "flv", rtmpURL.c_str()) < 0) {
        log::error("Failed to allocate output format context");
        return false;
    }

    // Open the output URL
    if (avio_open(&formatContext->pb, rtmpURL.c_str(), AVIO_FLAG_WRITE) < 0) {
        log::error("Failed to open RTMP URL");
        avformat_free_context(formatContext);
        return false;
    }

    // Create video stream
    videoStream = avformat_new_stream(formatContext, nullptr);
    if (!videoStream) {
        log::error("Failed to create video stream");
        avio_closep(&formatContext->pb);
        avformat_free_context(formatContext);
        return false;
    }

    // Configure codec parameters for the stream
    AVCodec* codec = avcodec_find_encoder(AV_CODEC_ID_H264);
    if (!codec) {
        log::error("H.264 encoder not found");
        avio_closep(&formatContext->pb);
        avformat_free_context(formatContext);
        return false;
    }

    AVCodecContext* codecContext = avcodec_alloc_context3(codec);
    if (!codecContext) {
        log::error("Failed to allocate codec context");
        avio_closep(&formatContext->pb);
        avformat_free_context(formatContext);
        return false;
    }

    codecContext->codec_id = codec->id;
    codecContext->bit_rate = 400000;
    codecContext->width = 1280;
    codecContext->height = 720;
    codecContext->time_base = (AVRational){1, 30}; // 30 FPS
    codecContext->framerate = (AVRational){30, 1};
    codecContext->gop_size = 10; // Group of Pictures size
    codecContext->max_b_frames = 1;
    codecContext->pix_fmt = AV_PIX_FMT_YUV420P;

    if (formatContext->oformat->flags & AVFMT_GLOBALHEADER)
        codecContext->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;

    // Open codec
    if (avcodec_open2(codecContext, codec, nullptr) < 0) {
        log::error("Failed to open codec");
        avcodec_free_context(&codecContext);
        avio_closep(&formatContext->pb);
        avformat_free_context(formatContext);
        return false;
    }

    // Copy the codec context settings to the stream
    if (avcodec_parameters_from_context(videoStream->codecpar, codecContext) < 0) {
        log::error("Failed to copy codec context parameters");
        avcodec_free_context(&codecContext);
        avio_closep(&formatContext->pb);
        avformat_free_context(formatContext);
        return false;
    }

    videoStream->time_base = codecContext->time_base;

    // Write the stream header
    if (avformat_write_header(formatContext, nullptr) < 0) {
        log::error("Failed to write header to RTMP stream");
        avcodec_free_context(&codecContext);
        avio_closep(&formatContext->pb);
        avformat_free_context(formatContext);
        return false;
    }

    log::info("RTMP stream initialized and ready to receive frames.");

    // Clean up (typically, you'd handle this after streaming is done)
    av_write_trailer(formatContext);
    avcodec_free_context(&codecContext);
    avio_closep(&formatContext->pb);
    avformat_free_context(formatContext);

    return true;
}

$execute {
    auto accountID = GJAccountManager::sharedState()->m_accountID;
    if (Stream::init(accountID, "Test Livestream")) {
        Stream::startRTMPStream("TestLivestream");
    }
}
