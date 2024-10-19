package com.neurotec.tutorials.biometrics;

import java.util.EnumSet;

import com.neurotec.biometrics.NBiometricOperation;
import com.neurotec.biometrics.NBiometricStatus;
import com.neurotec.biometrics.NIris;
import com.neurotec.biometrics.NSubject;
import com.neurotec.biometrics.NTemplateSize;
import com.neurotec.biometrics.client.NBiometricClient;
import com.neurotec.biometrics.client.NClusterBiometricConnection;
import com.neurotec.io.NFile;
import com.neurotec.tutorials.util.LibraryManager;
import com.neurotec.tutorials.util.Utils;

public final class CreateIrisTemplateOnServer {
	private static final String DESCRIPTION = "Demonstrates how to create iris template from image on server";
	private static final String NAME = "create-iris-template-on-server";
	private static final String VERSION = "13.1.0.0";

	private static final String DEFAULT_ADDRESS = "127.0.0.1";
	private static final int DEFAULT_SERVER_PORT = 24932;
	private static final int DEFAULT_CLIENT_PORT = 25452;

	private static void usage() {
		System.out.println("usage:");
		System.out.format("\t%s -s [server:adminPort] -c [clientPort] -i [inputImage] -t [outputTemplate]%n", NAME, DEFAULT_CLIENT_PORT);
		System.out.println();
		System.out.format("\t-s [server:adminPort]   - matching server address (optional parameter, if address specified - port is optional). Default: %d%n", DEFAULT_SERVER_PORT);
		System.out.format("\t-c [clientPort]   - matching client port (optional parameter). Default: %d%n", DEFAULT_CLIENT_PORT);
		System.out.println("\t-i [inputImage]   - image filename to store iris image.");
		System.out.println("\t-t [outputTemplate]   - filename to store iris template.");
		System.out.println();
		System.out.println();
		System.out.println("example:");
		System.out.format("\t%s -s 127.0.0.1 -c %d  -i image.jpg -t template.dat%n", NAME, DEFAULT_CLIENT_PORT);
	}

	public static void main(String[] args) {
		LibraryManager.initLibraryPath();

		Utils.printTutorialHeader(DESCRIPTION, NAME, VERSION, args);

		if (args.length < 3) {
			usage();
			System.exit(1);
		}

		ParseArgsResult parseArgsResult = null;

		try {
			parseArgsResult = parseArgs(args);
		} catch (Exception e) {
			usage();
			System.exit(-1);
		}

		try {
			NBiometricClient biometricClient = new NBiometricClient();
			NSubject subject = new NSubject();
			NIris iris = new NIris();

			// Perform all biometric operations on remote server only
			biometricClient.setLocalOperations(EnumSet.noneOf(NBiometricOperation.class));
			NClusterBiometricConnection connection = new NClusterBiometricConnection();
			connection.setHost(parseArgsResult.serverAddress);
			connection.setPort(parseArgsResult.clientPort);
			connection.setAdminPort(parseArgsResult.serverPort);
			biometricClient.getRemoteConnections().add(connection);

			iris.setSampleBuffer(NFile.readAllBytes(parseArgsResult.imageFile));

			subject.getIrises().add(iris);
			biometricClient.setIrisesTemplateSize(NTemplateSize.LARGE);

			NBiometricStatus status = biometricClient.createTemplate(subject);

			if (status == NBiometricStatus.OK) {
				System.out.println("Template extracted");
				NFile.writeAllBytes(parseArgsResult.templateFile, subject.getTemplateBuffer());
				System.out.println("Template saved successfully");
			} else {
				System.out.format("Extraction failed: %s\n", status);
			}

		} catch (Throwable th) {
			Utils.handleError(th);
		}
	}

	private static ParseArgsResult parseArgs(String[] args) throws Exception {
		ParseArgsResult result = new ParseArgsResult();
		result.serverAddress = DEFAULT_ADDRESS;
		result.serverPort = DEFAULT_SERVER_PORT;
		result.clientPort = DEFAULT_CLIENT_PORT;

		result.imageFile = "";
		result.templateFile = "";

		for (int i = 0; i < args.length; i++) {
			String optarg = "";

			if (args[i].length() != 2 || args[i].charAt(0) != '-') {
				throw new Exception("Parameter parse error");
			}

			if (args.length > i + 1 && args[i + 1].charAt(0) != '-') {
				optarg = args[i + 1]; // we have a parameter for given flag
			}

			if (optarg == "") {
				throw new Exception("Parameter parse error");
			}

			switch (args[i].charAt(1)) {
			case 's':
				i++;
				if (optarg.contains(":")) {
					String[] splitAddress = optarg.split(":");
					result.serverAddress = splitAddress[0];
					result.serverPort = Integer.parseInt(splitAddress[1]);
				} else {
					result.serverAddress = optarg;
					result.serverPort = DEFAULT_SERVER_PORT;
				}
				break;
			case 'c':
				i++;
				result.clientPort = Integer.parseInt(optarg);
				break;
			case 'i':
				i++;
				result.imageFile = optarg;
				break;
			case 't':
				i++;
				result.templateFile = optarg;
				break;
			default:
				throw new Exception("Wrong parameter found!");
			}
		}
		if (result.imageFile.equals("")) throw new Exception("Image - required parameter not specified");
		if (result.templateFile.equals("")) throw new Exception("Template - required parameter not specified");
		return result;
	}

	private static class ParseArgsResult {
		private String serverAddress;
		private int serverPort;
		private int clientPort;
		private String imageFile;
		private String templateFile;
	}
}