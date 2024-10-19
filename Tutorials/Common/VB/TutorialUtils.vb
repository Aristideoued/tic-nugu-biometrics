Imports Microsoft.VisualBasic
Imports System
Imports System.Diagnostics
Imports System.IO
Imports System.Reflection

Public NotInheritable Class TutorialUtils
	Private Sub New()
	End Sub

	Public Shared Function GetTrialModeFlag() As Boolean
		Dim filePath = AppDomain.CurrentDomain.BaseDirectory + "../Licenses/TrialFlag.txt"
		If File.Exists(filePath) Then
			Dim lines = File.ReadAllLines(filePath)
			If lines.Length > 0 AndAlso lines(0).Trim().ToLower().Equals("true") Then
				Return True
			End If
		Else
			Console.WriteLine("Failed to locate file: " + Path.GetFullPath(filePath))
		End If
		Return False
	End Function

	Public Shared Sub PrintTutorialHeader(ByVal args() As String)
		Dim description As String = (CType(Assembly.GetExecutingAssembly().GetCustomAttributes(GetType(AssemblyDescriptionAttribute), False)(0), AssemblyDescriptionAttribute)).Description
		Dim version As String = FileVersionInfo.GetVersionInfo(Assembly.GetExecutingAssembly().Location).FileVersion
		Dim copyright As String = (CType(Assembly.GetExecutingAssembly().GetCustomAttributes(GetType(AssemblyCopyrightAttribute), False)(0), AssemblyCopyrightAttribute)).Copyright
		Console.WriteLine(GetAssemblyName())
		Console.WriteLine("")
		Console.WriteLine("{0} (Version: {1})", description, version)
		Console.WriteLine(copyright.Replace("?", "(C)"))
		Console.WriteLine()
		If args IsNot Nothing AndAlso args.Length > 0 Then
			Console.WriteLine("Arguments:")
			For Each item As String In args
				Console.WriteLine(vbTab & "{0}", item)
			Next item
			Console.WriteLine()
		End If
	End Sub

	Public Shared Function GetAssemblyName() As String
		Return Assembly.GetExecutingAssembly().GetName().Name
	End Function

	Public Shared Function PrintException(ByVal ex As Exception) As Integer
		Dim errorCode As Integer = -1
		Console.WriteLine(ex)

		Do While (TypeOf ex Is AggregateException) AndAlso (ex.InnerException IsNot Nothing)
			ex = ex.InnerException
		Loop

		Dim neurotecException As INeurotecException = TryCast(ex, INeurotecException)
		If neurotecException IsNot Nothing Then
			errorCode = neurotecException.Code
		End If
		Return errorCode
	End Function
End Class
