package com.neurotec.samples.util;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.ImageFormat;
import android.graphics.Matrix;
import android.graphics.Rect;
import android.graphics.RectF;
import android.graphics.YuvImage;
import android.net.Uri;
import android.os.Environment;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.ByteBuffer;

public final class BitmapUtils {

	// ===========================================================
	// Private static fields
	// ===========================================================

	private static final int DEFAULT_WIDTH = 1280;
	private static final int DEFAULT_HEIGHT = 760;

	// ===========================================================
	// Private constructor
	// ===========================================================

	private BitmapUtils() {
	}

	// ===========================================================
	// Public static methods
	// ===========================================================

	public static Bitmap cropRotateScaleImage(Bitmap image, Rect rect, float rotation, int containerWidth, int containerHeight, Matrix resultMatrix) {
		Matrix matrix1 = new Matrix();
		matrix1.postRotate(rotation, image.getWidth() / 2F, image.getHeight() / 2F);

		Bitmap rotatedBitmap = Bitmap.createBitmap(image, 0, 0, image.getWidth(), image.getHeight(), matrix1, true);
		int diffX = (rotatedBitmap.getWidth() - image.getWidth()) / 2;
		int diffY = (rotatedBitmap.getHeight() - image.getHeight()) / 2;
		matrix1.postTranslate(diffX, diffY);

		float center[] = new float[] { rect.centerX(), rect.centerY() };
		matrix1.mapPoints(center);

		Matrix translateRectMatrix = new Matrix();
		translateRectMatrix.setTranslate(center[0] - rect.centerX(), center[1] - rect.centerY());
		RectF mappedRect = new RectF(rect);
		translateRectMatrix.mapRect(mappedRect);

		float scale = 1f;
		if ((containerWidth > 0) && (containerHeight > 0)) {
			scale = Math.min((float) containerWidth / mappedRect.width(), (float) containerHeight / mappedRect.height());
		}

		resultMatrix.set(matrix1);
		resultMatrix.postTranslate(-mappedRect.left, -mappedRect.top);
		resultMatrix.postScale(scale, scale);

		Matrix matrix2 = new Matrix();
		matrix2.postScale(scale, scale);

		mappedRect.left = Math.max(0, mappedRect.left);
		mappedRect.top = Math.max(0, mappedRect.top);
		mappedRect.right = Math.min(rotatedBitmap.getWidth(), mappedRect.right);
		mappedRect.bottom = Math.min(rotatedBitmap.getHeight(), mappedRect.bottom);

		return Bitmap.createBitmap(rotatedBitmap, (int) mappedRect.left, (int) mappedRect.top, (int) mappedRect.width(), (int) mappedRect.height(), matrix2, true);
	}

	public static Bitmap fromData(byte[] data, int width, int height) throws IOException {
		try (ByteArrayOutputStream baos = new ByteArrayOutputStream()) {
			YuvImage yuvimage = new YuvImage(data, ImageFormat.NV21, width, height, null);
			yuvimage.compressToJpeg(new Rect(0, 0, width, height), 80, baos);
			byte[] bitmapData = baos.toByteArray();
			return BitmapFactory.decodeByteArray(bitmapData, 0, bitmapData.length);
		}
	}

	public static Bitmap fromRawData(byte[] rawImage, int width, int height) {
		byte[] bits = new byte[rawImage.length * 4]; // RGBA.
		for (int j = 0; j < rawImage.length; j++) {
			bits[j * 4] = rawImage[j];
			bits[j * 4 + 1] = rawImage[j];
			bits[j * 4 + 2] = rawImage[j];
			bits[j * 4 + 3] = -1; // Alpha.
		}
		Bitmap bitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
		bitmap.copyPixelsFromBuffer(ByteBuffer.wrap(bits));
		return bitmap;
	}

	public static Bitmap scaleBitmap(byte[] data) {
		if (data == null) throw new NullPointerException("data");
		Bitmap bitmap = null;
		try {
			bitmap = BitmapFactory.decodeByteArray(data , 0, data.length);
			return Bitmap.createScaledBitmap(bitmap, DEFAULT_WIDTH, DEFAULT_HEIGHT, true);
		} finally {
			if (bitmap != null) {
				bitmap.recycle();
				bitmap = null;
			}
		}
	}

	public static Bitmap fromUri(Context context, Uri uri) throws IOException {
		if (context == null) throw new NullPointerException("context");
		if (uri == null) throw new NullPointerException("uri");

		try (InputStream is = context.getContentResolver().openInputStream(uri)) {
			//Decode image size
			BitmapFactory.Options o = new BitmapFactory.Options();
			o.inJustDecodeBounds = true;
			BitmapFactory.decodeStream(is, null, o);
			int scale = 1;
			int h = (int) Math.ceil(o.outHeight / (float) DEFAULT_HEIGHT);
			int w = (int) Math.ceil(o.outWidth / (float) DEFAULT_WIDTH);
			if (h > 1 || w > 1) {
				scale = Math.max(h, w);
			}
			//Decode with inSampleSize
			BitmapFactory.Options o2 = new BitmapFactory.Options();
			o2.inSampleSize = scale;
			try (InputStream is2 = context.getContentResolver().openInputStream(uri)) {
				return BitmapFactory.decodeStream(is2, null, o2);
			}
		} catch (FileNotFoundException e) {
			throw new IOException("File not found");
		}
	}

	public static void save(Bitmap bitmap, String filename) throws IOException {
		if (bitmap == null) throw new NullPointerException("bitmap");
		if (filename == null) throw new NullPointerException("filename");

		if (!EnvironmentUtils.isSdPresent()) {
			throw new IllegalStateException("SD card is not ready");
		}
		String path = Environment.getExternalStorageDirectory().toString();
		try {
			File file = new File(path, filename);
			try (OutputStream os = new FileOutputStream(file)) {
				bitmap.compress(Bitmap.CompressFormat.JPEG, 85, os);
			}
		} catch (FileNotFoundException e) {
			throw new IOException("File not found");
		}
	}

	public static void save(Context context, Bitmap bitmap, Uri uri) throws IOException {
		if (context == null) throw new NullPointerException("context");
		if (bitmap == null) throw new NullPointerException("bitmap");
		if (uri == null) throw new NullPointerException("uri");

		try (OutputStream os = context.getContentResolver().openOutputStream(uri)) {
			bitmap.compress(Bitmap.CompressFormat.JPEG, 90, os);
		} catch (FileNotFoundException e) {
			throw new IOException("File not found");
		}
	}
}
