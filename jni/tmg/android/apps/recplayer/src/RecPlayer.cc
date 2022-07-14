/*
 * RecPlayer.cc
 *
 *  Created on: 4 Feb 2015
 *      Author: Khanh Tran
 */

#include <jni_helper.h>
#include <sstream>
#include <android/bitmap.h>
#include <android/log.h>
#include <tmg/recplayer/recfile.h>

#include <libjpeg-turbo/turbojpeg.h>

using namespace tmg::recplayer;

#ifdef __cplusplus
extern "C" {

#endif
  /*
   * Class:     tmg_android_apps_recplayer_RecPlayer
   * Method:    open
   * Signature: (Ljava/lang/String;)J
   */
  JNIEXPORT jlong JNICALL
  Java_tmg_android_apps_recplayer_RecPlayer_open(JNIEnv *, jclass, jstring);

  /*
   * Class:     tmg_android_apps_recplayer_RecPlayer
   * Method:    getWidth
   * Signature: (J)I
   */
  JNIEXPORT jint JNICALL
  Java_tmg_android_apps_recplayer_RecPlayer_getWidth(JNIEnv *, jclass, jlong);

  /*
   * Class:     tmg_android_apps_recplayer_RecPlayer
   * Method:    getHeight
   * Signature: (J)I
   */
  JNIEXPORT jint JNICALL
  Java_tmg_android_apps_recplayer_RecPlayer_getHeight(JNIEnv *, jclass, jlong);

  /*
   * Class:     tmg_android_apps_recplayer_RecPlayer
   * Method:    getFrameRate
   * Signature: (J)D
   */
  JNIEXPORT jdouble JNICALL
  Java_tmg_android_apps_recplayer_RecPlayer_getFrameRate(JNIEnv *, jclass,
    jlong);

  /*
   * Class:     tmg_android_apps_recplayer_RecPlayer
   * Method:    close
   * Signature: (J)V
   */
  JNIEXPORT void JNICALL
  Java_tmg_android_apps_recplayer_RecPlayer_close(JNIEnv *, jclass, jlong);

  JNIEXPORT jboolean JNICALL
  Java_tmg_android_apps_recplayer_RecPlayer_render(JNIEnv* env, jclass clazz,
    jlong file, jobject bitmap);

  JNIEXPORT jstring JNICALL
  Java_tmg_android_apps_recplayer_RecPlayer_parseRiff(JNIEnv * env,
    jobject thiz, jstring filename);

  JNIEXPORT jbyteArray JNICALL
  Java_tmg_android_apps_recplayer_RecPlayer_readFrame(JNIEnv* env, jclass clazz,
    jlong file);
#ifdef __cplusplus
}
#endif

JNIEXPORT jlong JNICALL
Java_tmg_android_apps_recplayer_RecPlayer_open(JNIEnv * env, jclass thiz,
  jstring filename) {
  cstring path(env, filename);

  RecFile* file = new RecFile(path.c_str());
  if (file && file->open()) {
    return reinterpret_cast<jlong>(file);
  }

  return 0;
}

JNIEXPORT jint JNICALL
Java_tmg_android_apps_recplayer_RecPlayer_getWidth(JNIEnv *, jclass,
  jlong file) {
  if (file) {
    return reinterpret_cast<RecFile*>(file)->getWidth();
  }

  return 0;
}

JNIEXPORT jint JNICALL
Java_tmg_android_apps_recplayer_RecPlayer_getHeight(JNIEnv *, jclass,
  jlong file) {
  if (file) {
    return reinterpret_cast<RecFile*>(file)->getHeight();
  }

  return 0;
}

JNIEXPORT jdouble JNICALL
Java_tmg_android_apps_recplayer_RecPlayer_getFrameRate(JNIEnv *, jclass,
  jlong file) {
  if (file) {
    RecFile* f = reinterpret_cast<RecFile*>(file);
    return f->getFrameRate() / f->getFrameScale();
  }

  return 0;
}

JNIEXPORT void JNICALL
Java_tmg_android_apps_recplayer_RecPlayer_close(JNIEnv *, jclass, jlong file) {
  if (file) {
    RecFile* f = reinterpret_cast<RecFile*>(file);
    delete f;
  }
}
//
///* this function is from Android NDK bitmap-plasma , and modify for green color bug */
//inline uint16_t
//make565(int r, int g, int b) {
//  return (uint16_t) (((r << 8) & 0xf800) | ((g << 3) & 0x07e0)
//      | ((b >> 3) & 0x001f));
//}
//
//static void
//_JpegError(j_common_ptr cinfo) {
//  char pszMessage[JMSG_LENGTH_MAX];
//
//  (*cinfo->err->format_message)(cinfo, pszMessage);
//
//  __android_log_print(ANDROID_LOG_INFO, "Test118", "error!  %s", pszMessage);
//}

//static bool
//decodeJpeg(char* data, uint32_t size, JNIEnv* env, jobject bitmap) {
//
//  if (bitmap) {
//    AndroidBitmapInfo bmInfo;
//
//    if (AndroidBitmap_getInfo(env, bitmap, &bmInfo) < 0
//        || bmInfo.format != ANDROID_BITMAP_FORMAT_RGB_565) {
//      return false;
//    }
//
//    char* pixels;
//    if (AndroidBitmap_lockPixels(env, bitmap, &(void*&)pixels) >= 0) {
//      jpeg_decompress_struct jpegInfo;
//      jpeg_error_mgr jError;
//
//      jpegInfo.err = jpeg_std_error(&jError);
//      jError.error_exit = _JpegError;
//
//      jpeg_create_decompress(&jpegInfo);
//      jpeg_mem_src(&jpegInfo, (unsigned char*) data, size);
//      jpeg_read_header(&jpegInfo, TRUE);
//      jpeg_start_decompress(&jpegInfo);
//
//      int nJpegLineBytes = jpegInfo.output_width * jpegInfo.output_components;
//
//      JSAMPLE* pSample = new JSAMPLE[nJpegLineBytes + 10];
//      JSAMPROW buffer[] =
//      { pSample };
//
//      int yy = 0;
//      while (jpegInfo.output_scanline < jpegInfo.output_height) {
//        if (yy >= bmInfo.height)
//          break;
//
//        jpeg_read_scanlines(&jpegInfo, buffer, 1); //Jpegを1ライン読み込む
//
//        uint16_t* pLine = (uint16_t*) pixels;
//        for (int xx = 0, x3 = 0; xx < bmInfo.width && x3 < nJpegLineBytes;
//            xx++, x3 += 3) {
//          pLine[xx] = make565(buffer[0][x3 + 0], buffer[0][x3 + 1],
//              buffer[0][x3 + 2]);
//        }
//
//        // go to next line
//        pixels += bmInfo.stride;
//        yy++;
//      }
//      delete[] pSample;
//      jpeg_finish_decompress(&jpegInfo);
//      jpeg_destroy_decompress(&jpegInfo);
//
//      AndroidBitmap_unlockPixels(env, bitmap);
//
//      return true;
//    }
//  }
//
//  return false;
//}
static bool
decodeJpeg(char* data, uint32_t size, JNIEnv* env, jobject bitmap) {

  if (bitmap) {
    AndroidBitmapInfo bmInfo;

    if (AndroidBitmap_getInfo(env, bitmap, &bmInfo) < 0
        || bmInfo.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
      return false;
    }

    char* pixels;
    if (AndroidBitmap_lockPixels(env, bitmap, &(void*&) pixels) >= 0) {
      tjhandle jpegDec = tjInitDecompress();

      int width, height, jpegSubsamp;
      if (tjDecompressHeader2(jpegDec, (unsigned char *) data, size, &width,
          &height, &jpegSubsamp) == 0) {

        tjDecompress2(jpegDec, (unsigned char *) data, size,
            (unsigned char *) pixels, width, 0, height, TJPF::TJPF_RGBX, 0);

        tjDestroy(jpegDec);
      }

      AndroidBitmap_unlockPixels(env, bitmap);

      return true;
    }
  }

  return false;
}
JNIEXPORT jboolean JNICALL
Java_tmg_android_apps_recplayer_RecPlayer_render(JNIEnv* env, jclass clazz,
  jlong file, jobject bitmap) {

  RecFile* f = reinterpret_cast<RecFile*>(file);
  uint32_t size = 0;
  char* frame = f->readFrame(size);

  jboolean result = decodeJpeg(frame, size, env, bitmap) ? JNI_TRUE : JNI_FALSE;

  delete[] frame;

  return result;
}

JNIEXPORT jbyteArray JNICALL
Java_tmg_android_apps_recplayer_RecPlayer_readFrame(JNIEnv* env, jclass clazz,
  jlong file) {

  RecFile* f = reinterpret_cast<RecFile*>(file);
  uint32_t size = 0;
  char* frame = f->readFrame(size);
  if (frame) {
    jbyteArray result = env->NewByteArray(size);
    env->SetByteArrayRegion(result, 0, size, (const jbyte*) frame);

    delete[] frame;

    return result;
  }

  return NULL;
}

JNIEXPORT jstring JNICALL
Java_tmg_android_apps_recplayer_RecPlayer_parseRiff(JNIEnv * env, jobject thiz,
  jstring filename) {
  cstring path(env, filename);
  std::stringstream ss;

  if (path) {
    std::ifstream ifile(path.c_str());
    if (ifile.is_open()) {
      auto r = tmg::riff::parseRiff(ifile);
      if (r) {
        r->print(ss);
      }
      else {
        ss << "Null";
      }
    }
    else {
      ss << "Khong the mo tap tin (" << path << ")";
    }

  }

  return env->NewStringUTF(ss.str().c_str());
}
