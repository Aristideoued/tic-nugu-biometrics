using Grpc.Core;
using Grpc.Net.Client;
using Neurotec.MegaMatcherAccelerator;
using static Neurotec.MegaMatcherAccelerator.AcceleratorTask.Types;

namespace Neurotec.Mma.Samples
{
	class AcceleratorClientSample
	{
		static void ExitWithUsageInstructions()
		{
			Console.WriteLine("args: <server address> <operation> <subject ID, if needed> <template path, if needed>");
			Console.WriteLine("operations: enroll, delete, update, verify, identify, count, list, get");
			Environment.Exit(1);
		}

		static void Main(string[] args)
		{
			if (args.Length < 2)
			{
				ExitWithUsageInstructions();
			}
			var serverAddress = args[0];
			var operation = args[1];
			switch (operation)
			{
			case "count":
				PerformGetSubjectCount(serverAddress);
				break;
			case "list":
				PerformListIds(serverAddress);
				break;
			case "get":
				if (args.Length < 4) ExitWithUsageInstructions();
				PerformGetSubject(serverAddress, args[2], args[3]);
				break;
			case "enroll":
				if (args.Length < 4) ExitWithUsageInstructions();
				PerformBiometricOperation(serverAddress, BiometricOperation.Enroll, args[2], args[3]);
				break;
			case "delete":
				if (args.Length < 3) ExitWithUsageInstructions();
				PerformBiometricOperation(serverAddress, BiometricOperation.Delete, args[2], "");
				break;
			case "update":
				if (args.Length < 4) ExitWithUsageInstructions();
				PerformBiometricOperation(serverAddress, BiometricOperation.Enroll, args[2], args[3]);
				break;
			case "verify":
				if (args.Length < 4) ExitWithUsageInstructions();
				PerformBiometricOperation(serverAddress, BiometricOperation.Verify, args[2], args[3]);
				break;
			case "identify":
				if (args.Length < 3) ExitWithUsageInstructions();
				PerformBiometricOperation(serverAddress, BiometricOperation.Identify, "", args[2]);
				break;
			default:
				ExitWithUsageInstructions();
				break;
			}
		}

		static AcceleratorService.AcceleratorServiceClient GetServiceClient(string serverAddress)
		{
			GrpcChannel channel;

			if (System.Convert.ToBoolean(Environment.GetEnvironmentVariable("TLS_ENABLE")) == true)
			{
				channel = GrpcChannel.ForAddress("https://" + serverAddress, new GrpcChannelOptions
				{
					Credentials = ChannelCredentials.SecureSsl
				});
			}
			else
			{
				channel = GrpcChannel.ForAddress("http://" + serverAddress, new GrpcChannelOptions
				{
					Credentials = ChannelCredentials.Insecure
				});
			}

			return new AcceleratorService.AcceleratorServiceClient(channel);
		}

		static void PerformBiometricOperation(string serverAddress, BiometricOperation operation, string subjectId, string templatePath)
		{
			var mma = GetServiceClient(serverAddress);
			var req = new AcceleratorTask();
			req.Operation = operation;
			if (!string.IsNullOrEmpty(subjectId))
			{
				req.SubjectId = subjectId;
			}
			if (!string.IsNullOrEmpty(templatePath))
			{
				var templateData = File.ReadAllBytes(templatePath);
				req.Template = Google.Protobuf.ByteString.CopyFrom(templateData);
			}
			if (operation == BiometricOperation.Verify)
			{
				var param = new Parameter();
				param.Name = "Matching.WithDetails";
				param.IntValue = 1;
				req.MatchingParams.Add(param);
			}
			var result = mma.PerformTask(req);
			if (operation == BiometricOperation.Verify || operation == BiometricOperation.Identify)
			{
				PrintMatchingResults(result);
			}
		}

		static void PrintMatchingResults(AcceleratorResult result)
		{
			int count = result.MatchingResults.Count;
			Console.WriteLine("Matching results count: {0}", count);
			for (int i = 0; i < count; i++)
			{
				var mr = result.MatchingResults[i];
				Console.WriteLine("Result #{0}: matched with subject '{1}' with score: {2}", i, mr.SubjectId, mr.Score);
				if (mr.MatchingDetails != null)
				{
					PrintModalityDetails("Fingers", mr.MatchingDetails.FingerDetails);
					PrintModalityDetails("Faces", mr.MatchingDetails.FaceDetails);
					PrintModalityDetails("Irises", mr.MatchingDetails.IrisDetails);
					PrintModalityDetails("Palms", mr.MatchingDetails.PalmDetails);
					PrintModalityDetails("Voices", mr.MatchingDetails.VoiceDetails);
				}
			}
		}

		static void PrintModalityDetails(String modality, ModalityMatchingDetails? modalityDetails)
		{
			if (modalityDetails == null) return;
			Console.WriteLine("\t{0} matched with score: {1}", modality, modalityDetails.Score);
			for (int i = 0; i < modalityDetails.RecordDetails.Count; i++) {
				var recDetails = modalityDetails.RecordDetails[i];
				Console.WriteLine("\t\tRecord #{0} matched with score {1} with index {2}",
					i, recDetails.Score, recDetails.MatchedIndex);
			}
		}

		static void PerformGetSubjectCount(String serverAddress)
		{
			var mma = GetServiceClient(serverAddress);
			var result = mma.GetSubjectCount(new GetSubjectCountRequest());
			Console.WriteLine("Subject count: {0}", result.SubjectCount);
		}

		static void PerformListIds(String serverAddress)
		{
			var mma = GetServiceClient(serverAddress);
			String continuationToken = "";
			while (true)
			{
				var req = new ListIdsRequest();
				req.ContinuationToken = continuationToken;
				var result = mma.ListIdsPage(req);
				if (result.Ids.Count == 0) break;
				foreach (var id in result.Ids)
				{
					Console.WriteLine(id);
				}
				continuationToken = result.ContinuationToken;
			}
		}

		static void PerformGetSubject(String serverAddress, String subjectId, String outputPath)
		{
			var mma = GetServiceClient(serverAddress);
			var req = new GetSubjectRequest();
			req.SubjectId = subjectId;
			var result = mma.GetSubject(req);
			File.WriteAllBytes(outputPath, result.PackedTemplate.ToByteArray());
		}
	}
}