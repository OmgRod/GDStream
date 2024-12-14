#include "Stream.hpp"
#include "config.hpp"
#include <Geode/Geode.hpp>
#include <ffmpeg/libavformat/avformat.h>
#include <ffmpeg/libavformat/rtmp.h>
#include <ffmpeg/libavcodec/avcodec.h>
#include <ffmpeg/libavutil/avutil.h>
#include <ffmpeg/libavutil/opt.h>
#include <ffmpeg/libswscale/swscale.h>

using namespace geode::prelude;

class StreamSession {
public:
    AVFormatContext* formatContext = nullptr;
    AVStream* videoStream = nullptr;
    AVCodecContext* codecContext = nullptr;

    ~StreamSession() {
        cleanup();
    }

    void cleanup() {
        if (codecContext) {
            avcodec_free_context(&codecContext);
            codecContext = nullptr;
        }
        if (formatContext) {
            if (formatContext->pb) {
                avio_closep(&formatContext->pb);
            }
            avformat_free_context(formatContext);
            formatContext = nullptr;
        }
    }

    bool initialize(const char* filename) {
        avformat_network_init(); // Initialize network components

        int ret = avformat_open_input(&formatContext, filename, nullptr, nullptr);
        if (ret < 0) {
            cleanup();
            return false;
        }

        ret = avformat_find_stream_info(formatContext, nullptr);
        if (ret < 0) {
            cleanup();
            return false;
        }

        for (unsigned int i = 0; i < formatContext->nb_streams; i++) {
            if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
                videoStream = formatContext->streams[i];
                break;
            }
        }

        if (!videoStream) {
            cleanup();
            return false;
        }

        const AVCodec* codec = avcodec_find_decoder(videoStream->codecpar->codec_id);
        if (!codec) {
            cleanup();
            return false;
        }

        codecContext = avcodec_alloc_context3(codec);
        if (!codecContext) {
            cleanup();
            return false;
        }

        ret = avcodec_parameters_to_context(codecContext, videoStream->codecpar);
        if (ret < 0) {
            cleanup();
            return false;
        }

        ret = avcodec_open2(codecContext, codec, nullptr);
        if (ret < 0) {
            cleanup();
            return false;
        }

        return true;
    }
};

// Implementation of Stream class methods
bool Stream::init(int accountID, const std::string& streamName) {
    // Initialize the stream with the given account ID and stream name
    // Add your implementation here
    return true;
}

bool Stream::startRTMPStream(const std::string& streamName) {
    // Start the RTMP stream with the given stream name
    // Add your implementation here
    return true;
}