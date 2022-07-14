package tmg.android.apps.recplayer;

import java.util.concurrent.atomic.AtomicBoolean;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.os.Bundle;
import android.os.Environment;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class PlayerActivity extends Activity {
  /** Is playing. */
  private final AtomicBoolean isPlaying = new AtomicBoolean();
  /** Surface holder. */
  private SurfaceHolder surfaceHolder;

  private long rec = 0;

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_player);

    final String filename = Environment.getExternalStorageDirectory()
        + "/00000001.rec";

    rec = RecPlayer.open(filename);

    SurfaceView surfaceView = (SurfaceView) findViewById(R.id.surface_view);

    surfaceHolder = surfaceView.getHolder();
    surfaceHolder.addCallback(surfaceHolderCallback);

  }

  /**
   * Surface holder callback listens for surface events.
   */
  private final SurfaceHolder.Callback surfaceHolderCallback = new SurfaceHolder.Callback() {
    public void surfaceChanged(SurfaceHolder holder, int format, int width,
        int height) {
    }

    public void surfaceCreated(SurfaceHolder holder) {
      // Start playing since surface is ready
      isPlaying.set(true);
      // Start renderer on a separate thread
      new Thread(renderer).start();
    }

    public void surfaceDestroyed(SurfaceHolder holder) {
      // Stop playing since surface is destroyed
      isPlaying.set(false);
    }
  };

  /**
   * Renderer runnable renders the video frames from the AVI file to the surface
   * through a bitmap.
   */
  private final Runnable renderer = new Runnable() {
    public void run() {
      // Create a new bitmap to hold the frames
      Bitmap bitmap = Bitmap.createBitmap(RecPlayer.getWidth(rec),
          RecPlayer.getHeight(rec), Bitmap.Config.RGB_565);

      // Calculate the delay using the frame rate
      long frameDelay = (long) (1000 / RecPlayer.getFrameRate(rec));
      // Start rendering while playing
      while (isPlaying.get() && RecPlayer.render(rec, bitmap)) {
        // Lock canvas
        Canvas canvas = surfaceHolder.lockCanvas();

        // Draw the bitmap to the canvas
        canvas.drawBitmap(bitmap, 0, 0, null);

        // Post the canvas for displaying
        surfaceHolder.unlockCanvasAndPost(canvas);
        
        // Wait for the next frame
        try {
          Thread.sleep(frameDelay);
        } catch (InterruptedException e) {
          break;
        }
      }

      RecPlayer.close(rec);
    }
  };
}
