package com.neurotec.mma.samples;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import com.google.protobuf.ByteString;
import com.neurotec.mma.MMAProto.AcceleratorResult;
import com.neurotec.mma.MMAProto.AcceleratorTask;
import com.neurotec.mma.MMAProto.BiometricOperation;
import com.neurotec.mma.MMAProto.GetSubjectCountRequest;
import com.neurotec.mma.MMAProto.GetSubjectRequest;
import com.neurotec.mma.MMAProto.ListIdsRequest;
import com.neurotec.mma.MMAProto.ModalityMatchingDetails;

public class AcceleratorClientSample {
	private static void exitWithUsageInstructions() {
		System.out.println("args: <server address> <operation> <subject ID, if needed> <template path, if needed>");
		System.out.println("operations: enroll, delete, update, verify, identify, count, list, get");
		System.exit(1);
	}

	public static void main(String[] args) {
		if (args.length < 2) {
			exitWithUsageInstructions();
		}
		String serverAddress = args[0];
		String operationStr = args[1];
		String subjectId = args.length >= 3 ? args[2] : null;
		String templatePath = args.length >= 4 ? args[3] : null;
		BiometricOperation operation = BiometricOperation.NONE;
		int requiredArgsCount = 4;
		boolean isMatchingOperation = false;
		if (operationStr.equalsIgnoreCase("count")) {
			performGetSubjectCount(serverAddress);
			return;
		} else if (operationStr.equalsIgnoreCase("list")) {
			performListIds(serverAddress);
			return;
		} else if (operationStr.equalsIgnoreCase("get")) {
			if (args.length < requiredArgsCount) {
				exitWithUsageInstructions();
			}
			performGetSubject(serverAddress, subjectId, templatePath);
			return;
		} else if (operationStr.equalsIgnoreCase("enroll")) {
			operation = BiometricOperation.ENROLL;
		} else if (operationStr.equalsIgnoreCase("delete")) {
			operation = BiometricOperation.DELETE;
			requiredArgsCount = 3;
		} else if (operationStr.equalsIgnoreCase("update")) {
			operation = BiometricOperation.UPDATE;
		} else if (operationStr.equalsIgnoreCase("verify")) {
			operation = BiometricOperation.VERIFY;
			isMatchingOperation = true;
		} else if (operationStr.equalsIgnoreCase("identify")) {
			operation = BiometricOperation.IDENTIFY;
			templatePath = subjectId;
			requiredArgsCount = 3;
			isMatchingOperation = true;
		} else {
			exitWithUsageInstructions();
		}
		if (args.length < requiredArgsCount) {
			exitWithUsageInstructions();
		}

		try (var connection = AcceleratorConnection.open(serverAddress)) {
			var mma = connection.getStub();
			var task = AcceleratorTask.newBuilder()
				.setOperation(operation)
				.setSubjectId(subjectId);
			if (templatePath != null) {
				var template = Files.readAllBytes(Path.of(templatePath));
				task.setTemplate(ByteString.copyFrom(template));
			}
			if (isMatchingOperation) {
				var matchingParams = task.addMatchingParamsBuilder();
				matchingParams.setName("Matching.WithDetails").setIntValue(1);
			}
			var result = mma.performTask(task.build());
			if (isMatchingOperation) {
				printMatchingResults(result);
			}
		} catch (Throwable th) {
			System.out.println("Error while performing task: " + th);
		}
	}

	private static void printMatchingResults(AcceleratorResult result) {
		int count = result.getMatchingResultsCount();
		System.out.println("Matching results count: " + count);
		for (int i = 0; i < count; i++) {
			var mr = result.getMatchingResults(i);
			System.out.println("Result #" + i + ": matched with subject '" + mr.getSubjectId() + "' with score: " + mr.getScore());
			if (mr.hasMatchingDetails()) {
				var matchingDetails = mr.getMatchingDetails();
				if (matchingDetails.hasFingerDetails()) {
					printModalityDetails("Fingers", matchingDetails.getFingerDetails());
				}
				if (matchingDetails.hasFaceDetails()) {
					printModalityDetails("Faces", matchingDetails.getFaceDetails());
				}
				if (matchingDetails.hasIrisDetails()) {
					printModalityDetails("Irises", matchingDetails.getIrisDetails());
				}
				if (matchingDetails.hasPalmDetails()) {
					printModalityDetails("Palms", matchingDetails.getPalmDetails());
				}
				if (matchingDetails.hasVoiceDetails()) {
					printModalityDetails("Voices", matchingDetails.getVoiceDetails());
				}
			}
		}
	}

	private static void printModalityDetails(String modality, ModalityMatchingDetails modalityDetails) {
		System.out.println("\t" + modality + " matched with score: " + modalityDetails.getScore());
		for (int i = 0; i < modalityDetails.getRecordDetailsCount(); i++) {
			var recDetails = modalityDetails.getRecordDetails(i);
			System.out.println("\t\tRecord #" + i + " matched with score " + recDetails.getScore() + " with index " + recDetails.getMatchedIndex());
		}
	}

	private static void performGetSubjectCount(String serverAddress) {
		try (var connection = AcceleratorConnection.open(serverAddress)) {
			var mma = connection.getStub();
			var result = mma.getSubjectCount(GetSubjectCountRequest.newBuilder().build());
			System.out.println("Subject count: " + result.getSubjectCount()); 
		} catch (Throwable th) {
			System.out.println("Error while performing task: " + th);
		}
	}

	private static void performListIds(String serverAddress) {
		try (var connection = AcceleratorConnection.open(serverAddress)) {
			var mma = connection.getStub();
			String continuationToken = "";
			while (true) {
				var result = mma.listIdsPage(ListIdsRequest.newBuilder().setContinuationToken(continuationToken).build());
				if (result.getIdsCount() == 0) {
					break;
				}
				for (String id: result.getIdsList()) {
					System.out.println(id);
				}
				continuationToken = result.getContinuationToken();
			}
		} catch (Throwable th) {
			System.out.println("Error while performing task: " + th);
		}
	}

	private static void performGetSubject(String serverAddress, String subjectId, String outputFileName) {
		try (var connection = AcceleratorConnection.open(serverAddress)) {
			var mma = connection.getStub();
			var result = mma.getSubject(GetSubjectRequest.newBuilder().setSubjectId(subjectId).build());
			Files.write(Paths.get(outputFileName), result.getPackedTemplate().toByteArray());
		} catch (Throwable th) {
			System.out.println("Error while performing task: " + th);
		}
	}
}
