package tmg.android.apps.recplayer;

import java.io.IOException;

import android.graphics.Bitmap;

public class RecPlayer {
  /**
   * Opens the given AVI file and returns a file descriptor.
   * 
   * @param fileName
   *          file name.
   * @return file descriptor.
   * @throws IOException
   */
  public native static long open(String fileName);

  /**
   * Get the video width.
   * 
   * @param avi
   *          file descriptor.
   * @return video width.
   */
  public native static int getWidth(long avi);

  public native static String parseRiff(String filename);

  /**
   * Get the video height.
   * 
   * @param avi
   *          file descriptor.
   * @return video height.
   */
  public native static int getHeight(long avi);

  /**
   * Gets the frame rate.
   * 
   * @param avi
   *          file descriptor.
   * @return frame rate.
   */
  public native static double getFrameRate(long avi);

  /**
   * Closes the given AVI file based on given file descriptor.
   * 
   * @param avi
   *          file descriptor.
   */
  public native static void close(long avi);

  public native static boolean render(long avi, Bitmap bitmap);

  public native static byte[] readFrame(long avi);

  static {
    System.loadLibrary("jpeg");
    System.loadLibrary("recplayer-tmg-wrapper");
  }
}
