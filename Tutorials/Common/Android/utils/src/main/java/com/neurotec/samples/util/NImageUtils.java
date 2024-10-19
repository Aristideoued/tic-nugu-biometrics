package com.neurotec.samples.util;

import android.content.Context;
import android.net.Uri;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.ByteBuffer;

import com.neurotec.images.NImage;
import com.neurotec.images.NImageFormat;
import com.neurotec.images.NPixelFormat;
import com.neurotec.io.NBuffer;
import com.neurotec.io.NStream;

public final class NImageUtils {

	// ===========================================================
	// Private static fields
	// ===========================================================

	private static final String ANDROID_ASSET_DESCRIPTOR = "file:///android_asset/";

	// ===========================================================
	// Private constructor
	// ===========================================================

	private NImageUtils() {
	}

	// ===========================================================
	// Public static methods
	// ===========================================================

	public static NImage fromData(byte[] data, int width, int height, int resolution) {
		NImage image = NImage.fromData(NPixelFormat.GRAYSCALE_8U, width, height, width, width, ByteBuffer.wrap(data));
		image.setHorzResolution(resolution);
		image.setVertResolution(resolution);
		return image;
	}

	public static NImage fromUri(Context context, Uri uri) throws IOException {
		return fromUri(context, uri, null);
	}

	public static NImage fromUri(Context context, Uri uri, NImageFormat format) throws IOException {
		if (context == null) throw new NullPointerException("context");
		if (uri == null) throw new NullPointerException("uri");

		if (uri.toString().startsWith(ANDROID_ASSET_DESCRIPTOR)) {
			return NImage.fromFile(uri.toString().replace(ANDROID_ASSET_DESCRIPTOR, ""), format);
		} else {
			try (InputStream inputStream = context.getContentResolver().openInputStream(uri)) {
				return NImage.fromStream(NStream.fromInputStream(inputStream), format);
			}
		}
	}

	public static NImage fromUrl(String url) throws IOException {
		if (url == null) throw new NullPointerException("uri");
		return NImage.fromFile(url);
	}

	public static NImage fromJPEG(byte[] data) {
		NBuffer srcPixels = NBuffer.fromArray(data);
		return NImage.fromMemory(srcPixels, NImageFormat.getJPEG());
	}

	public static NImage fromNV21(byte[] data, int width, int height) {
		// Take only intensity (Y) data from preview byte buffer.
		NBuffer srcPixels = NBuffer.fromArray(data);
		return NImage.getWrapper(NPixelFormat.GRAYSCALE_8U, width, height, width, srcPixels);
	}

	public static void save(Context context, NImage image, Uri uri) throws IOException {
		if (context == null) throw new NullPointerException("context");
		if (image == null) throw new NullPointerException("image");
		if (uri == null) throw new NullPointerException("uri");

		try (OutputStream os = context.getContentResolver().openOutputStream(uri);
			 NStream stream = NStream.fromOutputStream(os)) {
			image.save(stream);
		} catch (FileNotFoundException e) {
			throw new IOException("File not found");
		}
	}
}
