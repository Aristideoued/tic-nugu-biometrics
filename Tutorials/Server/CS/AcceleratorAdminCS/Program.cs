using Neurotec.Accelerator.Admin.Rest.Api;
using Neurotec.Accelerator.Admin.Rest.Model;
using Neurotec.Licensing;
using System;
using System.Collections.Generic;
using System.IO;
using System.Threading;

namespace Neurotec.Tutorials
{
	public class Program
	{
		#region Console interface

		private const string DefaultUsername = "Admin";
		private const string DefaultPassword = "Admin";

		private static int Usage()
		{
			Console.WriteLine("usage:");
			Console.WriteLine("\t{0} [server] [command]", TutorialUtils.GetAssemblyName());
			Console.WriteLine("\tserver - matching server address");
			Console.WriteLine();
			Console.WriteLine("\tcommands:");
			Console.WriteLine("\t\tstart-cluster          - Start cluster");
			Console.WriteLine("\t\tstop-node              - Stop (wait until finished task in progress) node");
			Console.WriteLine("\t\tkill-node              - Instantly stop node");
			Console.WriteLine("\t\tlist-admin-tasks       - List administrative tasks");
			Console.WriteLine("\t\tlist-nodes             - List nodes");
			Console.WriteLine("\t\tcluster-status         - Gets current cluster status");
			Console.WriteLine("\t\tstatus                 - Gets full current cluster status");
			Console.WriteLine("\t\tcreate-backup <file>   - Creates database backup to a specified file");
			Console.WriteLine();

			return 1;
		}

		private static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);

			if (args.Length < 2)
			{
				return Usage();
			}

			//=========================================================================
			// TRIAL MODE
			//=========================================================================
			// Below code line determines whether TRIAL is enabled or not. To use purchased licenses, don't use below code line.
			// GetTrialModeFlag() method takes value from "Bin/Licenses/TrialFlag.txt" file. So to easily change mode for all our examples, modify that file.
			// Also you can just set TRUE to "TrialMode" property in code.

			NLicenseManager.TrialMode = TutorialUtils.GetTrialModeFlag();

			Console.WriteLine("Trial mode: " + NLicenseManager.TrialMode);

			//=========================================================================

			try
			{
				string server;
				try
				{
					server = args[0];

				}
				catch
				{
					Console.WriteLine("server address in wrong format.");
					return -1;
				}

				var cmd = new List<string>();
				for (int i = 1; i < args.Length; i++)
				{
					cmd.Add(args[i]);
				}

				var serverAdmin = new Program(server);
				serverAdmin.ExecuteCommand(cmd.ToArray());

				return 0;
			}
			catch (Exception ex)
			{
				return TutorialUtils.PrintException(ex);
			}
		}

		#endregion Console interface

		#region Server status info

		private readonly string _server;

		public Program(string server)
		{
			_server = server;
		}

		private string FormatServerAddress()
		{
			return String.Format("http://{0}/rs", _server);
		}

		private void WaitForTask(int taskId)
		{
			var apiInstance = new AdminTasksApi(FormatServerAddress());
			apiInstance.Configuration.Username = DefaultUsername;
			apiInstance.Configuration.Password = DefaultPassword;
			while (true)
			{
				var task = apiInstance.GetTask(taskId);
				if (task.Status.Value != Task.StatusEnum.RUNNING
					&& task.Status.Value != Task.StatusEnum.SUBMITTED)
				{
					Console.WriteLine("Task finished with status {0}", task.Status.Value);
					if (task.ErrorMessage != null)
						Console.WriteLine("Error message: {0}", task.ErrorMessage);
					break;
				}
				else
				{
					Console.WriteLine("Waiting for task {0}", task.Id);
					Thread.Sleep(500);
				}
			}
		}

		private void ClusterStatus()
		{
			var apiInstance = new ClusterAdminApi(FormatServerAddress());
			apiInstance.Configuration.Username = DefaultUsername;
			apiInstance.Configuration.Password = DefaultPassword;
			var status = apiInstance.GetClusterStatus();
			Console.WriteLine("Cluster status is: {0}", status.Stage);
			if (status.Stage == Accelerator.Admin.Rest.Model.ClusterStatus.StageEnum.LOADING)
			{
				Console.WriteLine("Loaded {0} out of {1} partitions", status.LoadedPartitionsCount, status.TotalPartitionsCount);
			}
		}

		private void StartCluster()
		{
			var apiInstance = new ClusterAdminApi(FormatServerAddress());
			apiInstance.Configuration.Username = DefaultUsername;
			apiInstance.Configuration.Password = DefaultPassword;
			var task = apiInstance.StartCluster();
			Console.WriteLine("start command sent successfully");
			WaitForTask(task.Id.Value);

		}

		private void StopNode()
		{
			var apiInstance = new NodeAdminApi(FormatServerAddress());
			apiInstance.Configuration.Username = DefaultUsername;
			apiInstance.Configuration.Password = DefaultPassword;

			var task = apiInstance.ShutdownNode();
			Console.WriteLine("stop node command sent successfully");
			WaitForTask(task.Id.Value);
		}

		private void KillNode()
		{
			var apiInstance = new NodeAdminApi(FormatServerAddress());
			apiInstance.Configuration.Username = DefaultUsername;
			apiInstance.Configuration.Password = DefaultPassword;

			var task = apiInstance.ShutdownNode(true);
			Console.WriteLine("kill node command sent successfully");
			WaitForTask(task.Id.Value);
		}

		private void NodesStatus()
		{
			var apiInstance = new NodesAdminApi(FormatServerAddress());
			apiInstance.Configuration.Username = DefaultUsername;
			apiInstance.Configuration.Password = DefaultPassword;
			var nodes = apiInstance.GetNodesStatus();
			if (nodes != null)
			{
				Console.WriteLine("{0} node(s) running:", nodes.Count);
			}

			foreach (var node in nodes)
			{
				Console.WriteLine("\tid: {0}", node.Id);
				Console.WriteLine("\tip address: {0}", node.IpAddress);
				Console.WriteLine("\tstatus: {0}", node.Stage);
				Console.WriteLine("\tloaded database partitions {0}/{1}", node.DatabaseLoadedPartitionsCount, node.DatabaseResponsiblePartitionsCount);
				Console.WriteLine("\tloaded engine partitions {0}/{1}", node.EngineLoadedPartitionsCount, node.EngineResponsiblePartitionsCount);
			}
			Console.WriteLine();
		}

		private void AdministrativeTasks()
		{
			var apiInstance = new AdminTasksApi(FormatServerAddress());
			apiInstance.Configuration.Username = DefaultUsername;
			apiInstance.Configuration.Password = DefaultPassword;
			var tasks = apiInstance.GetTasks();

			Console.WriteLine("{0} tasks(s):", tasks.Count);
			foreach (var task in tasks)
			{
				Console.WriteLine("\tid: {0}", task.Id);
				Console.WriteLine("\ttitle: {0}", task.Title);
				Console.WriteLine("\tprogress: {0}", task.Status);
				Console.WriteLine("\tcreated at: {0}", task.CreatedAt);
				Console.WriteLine("\tended at at: {0}", task.EndedAt);
				if (task.ErrorMessage != null)
				{
					Console.WriteLine("\terror message: {0}", task.ErrorMessage);
				}
				Console.WriteLine();
			}
			Console.WriteLine();
		}

		public void PrintServerStatus()
		{
			try
			{
				Console.WriteLine("asking info from {0}  ...", _server);
				Console.WriteLine();

				Console.WriteLine("requesting info about server ...");
				ClusterStatus();

				Console.WriteLine("requesting info about nodes ...");
				NodesStatus();

				Console.WriteLine("requesting info about administrative tasks ...");
				AdministrativeTasks();
			}
			catch (Exception ex)
			{
				Console.WriteLine("an error has occured");
				Console.WriteLine(ex);
			}
		}

		public void CreateBackup(string fileName)
		{
			var apiInstance = new DatabaseAdminApi(FormatServerAddress());
			apiInstance.Configuration.Username = DefaultUsername;
			apiInstance.Configuration.Password = DefaultPassword;

			using (var outputStream = new FileStream(fileName, FileMode.Create))
			{
				var status = apiInstance.GetDatabaseBackup(outputStream);
				Console.WriteLine("backup created");
				if (!string.IsNullOrEmpty(status))
				{
					Console.WriteLine(status);
				}
			}
		}

		private void ExecuteCommand(string[] args)
		{
			try
			{
				switch (args[0])
				{
					case "start-cluster":
						StartCluster();
						break;
					case "stop-node":
						StopNode();
						break;
					case "kill-node":
						KillNode();
						break;
					case "list-admin-tasks":
						AdministrativeTasks();
						break;
					case "list-nodes":
						NodesStatus();
						break;
					case "cluster-status":
						ClusterStatus();
						break;
					case "status":
						PrintServerStatus();
						break;
					case "create-backup":
						if (args.Length < 2)
						{
							Console.WriteLine("usage: create-backup <output filename>");
							return;
						}
						CreateBackup(args[1]);
						break;
					default:
						Console.WriteLine("command not recognized.");
						break;
				}
			}
			catch (Exception ex)
			{
				Console.WriteLine("an error has occured:");
				Console.WriteLine(ex);
			}
		}

		#endregion Server status info
	}
}
