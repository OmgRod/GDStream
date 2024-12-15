#ifndef RTMP_MANAGER_HPP
#define RTMP_MANAGER_HPP

#include <ffmpeg/libavformat/avformat.h>
#include <ffmpeg/libavcodec/avcodec.h>
#include <ffmpeg/libavutil/avutil.h>
#include <string>

class RTMPManager {
public:
    RTMPManager();
    ~RTMPManager();

    bool pushStream(const std::string& inputFile, const std::string& rtmpUrl);
    bool pullStream(const std::string& rtmpUrl);

private:
    bool pushToRTMP(const std::string& inputFile, const std::string& rtmpUrl);
    bool pullFromRTMP(const std::string& rtmpUrl);

    AVFormatContext* inputFormatContext = nullptr;
    AVFormatContext* outputFormatContext = nullptr;
    AVCodecContext* codecContext = nullptr;
    const AVCodec* codec = nullptr;  // Use const here

    bool isInitialized = false;
};

#endif // RTMP_MANAGER_HPP
