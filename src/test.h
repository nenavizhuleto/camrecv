
//#define H264
//#define FIFO
// #define WTF

// #ifdef H264
//
// #include "libavcodec/avcodec.h"
// #include "libavformat/avformat.h"
//
// #endif
//
// --------------------------------
	// fifo_fd = open(fifo, O_WRONLY);
	// if (fifo_fd < 0) {
	// 	printf("failed to open fifo\n");
	// 	return;
	// }
	//
	// printf("initialized fifo at %s\n", fifo);

// --------------------------------

// #ifdef H264
// 	const AVCodec *dec = avcodec_find_decoder(AV_CODEC_ID_MJPEG);
// 	if (NULL == dec) {
// 		printf("failed to find mjpeg decoder\n");
// 		return;
// 	}
// 	const AVCodec *enc = avcodec_find_encoder(AV_CODEC_ID_H264);
// 	if (NULL == enc) {
// 		printf("failed to find h264 encoder\n");
// 		return;
// 	}
//
// 	AVCodecContext* in_ctx = avcodec_alloc_context3(dec);
// 	if (NULL == in_ctx) {
// 		printf("failed to alloc context\n");
// 		return;
// 	}
//
// 	avcodec_open2(in_ctx, dec, NULL);
//
// 	AVCodecContext* out_ctx = avcodec_alloc_context3(enc);
// 	if (NULL == out_ctx) {
// 		printf("failed to alloc context\n");
// 		return;
// 	}
//
// 	out_ctx->width = 480;
// 	out_ctx->height = 320;
// 	out_ctx->pix_fmt = AV_PIX_FMT_YUV420P;
// 	out_ctx->time_base = (AVRational){1, 25};
// 	avcodec_open2(out_ctx, enc, NULL);
//
// 	AVFrame *frame = av_frame_alloc();
// 	AVPacket *pkt = av_packet_alloc();
// 	AVPacket *pkt2 = av_packet_alloc();
// #endif
// --------------------------------
// #ifdef H264
// 		uint8_t *data = av_malloc(n);
// 		memcpy(data, buf, n);
// 		printf("allocated packet data\n");
//
// 		if (av_packet_from_data(pkt, data, n) < 0) {
// 			printf("failed to create packet\n");
// 			break;
// 		}
// 		printf("created packet from data\n");
//
// 		int ret = avcodec_send_packet(in_ctx, pkt);
// 		if (ret < 0) {
// 			printf("failed to send packet to decoder: %s\n", av_err2str(ret));
// 			continue;
// 		}
//
// 		printf("send packet to decoder\n");
//
// 		while (ret >= 0) {
// 			ret = avcodec_receive_frame(in_ctx, frame);
// 			if (ret == AVERROR_EOF) {
// 				break;
// 			}
//
// 			printf("received frame from decoder\n");
//
// 			ret = avcodec_send_frame(out_ctx, frame);
// 			if (ret < 0) {
// 				printf("failed to send frame to encoder: %s\n", av_err2str(ret));
// 				continue;
// 			}
//
// 			printf("send frame to encoder\n");
//
// 			while (ret >= 0) {
// 				ret = avcodec_receive_packet(out_ctx, pkt2);
// 				if (ret == AVERROR_EOF) {
// 					break;
// 				}
//
// 				write(fifo_fd, pkt2->data, sizeof(pkt2->data));
//
// 				printf("received packet from encoder\n");
// 			}
//
// 			av_frame_unref(frame);
// 			av_packet_unref(pkt);
// 		}
//
// #endif
// --------------------------------
		// write frame to jpeg file
		// if (fprintf(fd, "%s", buf) < 0) {
		// 	printf("failed to write to the file: %s\n", strerror(errno));
		// }
// --------------------------------
		// write frame to system fifo
		// write(fifo_fd, buf, n + 2);
		//
		// printf("pushed to fifo\n");
// --------------------------------
// #ifdef FIFO
// 	mkfifo(fifo, 0666);
// #endif
