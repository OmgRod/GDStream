/*
#include "RTMPManager.hpp"
#include <Geode/Geode.hpp>

using namespace geode::prelude;

RTMPManager::RTMPManager() {
    // Initialize libavformat and libavcodec
    avformat_network_init(); // No need to call av_register_all() in newer versions
    isInitialized = true;
    log::debug("RTMPManager initialized.");
}

RTMPManager::~RTMPManager() {
    if (inputFormatContext) {
        avformat_close_input(&inputFormatContext);
    }
    if (outputFormatContext) {
        avformat_free_context(outputFormatContext);
    }
    if (codecContext) {
        avcodec_free_context(&codecContext);
    }
    log::debug("RTMPManager cleaned up.");
}

bool RTMPManager::pushStream(const std::string& inputFile, const std::string& rtmpUrl) {
    if (!isInitialized) {
        log::error("RTMPManager is not initialized properly.");
        return false;
    }

    log::info("Starting push stream to RTMP server: " + rtmpUrl);
    return pushToRTMP(inputFile, rtmpUrl);
}

bool RTMPManager::pullStream(const std::string& rtmpUrl) {
    if (!isInitialized) {
        log::error("RTMPManager is not initialized properly.");
        return false;
    }

    log::info("Starting pull stream from RTMP server: " + rtmpUrl);
    return pullFromRTMP(rtmpUrl);
}

bool RTMPManager::pushToRTMP(const std::string& inputFile, const std::string& rtmpUrl) {
    log::info("Opening input file: " + inputFile);

    if (avformat_open_input(&inputFormatContext, inputFile.c_str(), nullptr, nullptr) < 0) {
        log::error("Could not open input file: " + inputFile);
        return false;
    }

    if (avformat_find_stream_info(inputFormatContext, nullptr) < 0) {
        log::error("Could not find stream information.");
        return false;
    }

    AVStream* inputStream = inputFormatContext->streams[0]; // Assuming video stream is first

    log::info("Opening output stream: " + rtmpUrl);
    if (avformat_alloc_output_context2(&outputFormatContext, nullptr, "flv", rtmpUrl.c_str()) < 0) {
        log::error("Could not create output context for RTMP stream.");
        return false;
    }

    // Find and open the codec
    const AVCodec* codec = avcodec_find_encoder(inputStream->codecpar->codec_id); // Use const
    if (!codec) {
        log::error("Codec not found.");
        return false;
    }

    codecContext = avcodec_alloc_context3(codec);
    if (avcodec_open2(codecContext, codec, nullptr) < 0) {
        log::error("Could not open codec.");
        return false;
    }

    AVStream* outputStream = avformat_new_stream(outputFormatContext, codec);
    if (!outputStream) {
        log::error("Failed to create output stream.");
        return false;
    }

    // Write header for RTMP stream
    if (avformat_write_header(outputFormatContext, nullptr) < 0) {
        log::error("Error writing RTMP header.");
        return false;
    }

    // Send video frames to RTMP server
    AVPacket packet;
    while (av_read_frame(inputFormatContext, &packet) >= 0) {
        if (av_interleaved_write_frame(outputFormatContext, &packet) < 0) {
            log::error("Error writing frame to RTMP stream.");
            return false;
        }
        av_packet_unref(&packet);
    }

    av_write_trailer(outputFormatContext);
    return true;
}

bool RTMPManager::pullFromRTMP(const std::string& rtmpUrl) {
    log::info("Opening RTMP stream: " + rtmpUrl);

    if (avformat_open_input(&inputFormatContext, rtmpUrl.c_str(), nullptr, nullptr) < 0) {
        log::error("Could not open RTMP stream: " + rtmpUrl);
        return false;
    }

    if (avformat_find_stream_info(inputFormatContext, nullptr) < 0) {
        log::error("Could not find stream information.");
        return false;
    }

    AVStream* stream = inputFormatContext->streams[0]; // Assuming video stream is first
    log::info("Stream opened successfully.");

    // Process the stream (e.g., display or save frames)
    AVPacket packet;
    while (av_read_frame(inputFormatContext, &packet) >= 0) {
        // For simplicity, just discard the packets here, could process or save them
        av_packet_unref(&packet);
    }

    return true;
}
*/