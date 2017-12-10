<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="16008000">
	<Item Name="My Computer" Type="My Computer">
		<Property Name="NI.SortType" Type="Int">3</Property>
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="FallSensor" Type="Folder">
			<Item Name="GetPackets" Type="Folder">
				<Item Name="GPState.ctl" Type="VI" URL="../FallSensor/GetPackets/GPState.ctl"/>
				<Item Name="GPContext.ctl" Type="VI" URL="../FallSensor/GetPackets/GPContext.ctl"/>
			</Item>
			<Item Name="ReadingUnits" Type="Folder">
				<Item Name="AccelReadingUnit.ctl" Type="VI" URL="../FallSensor/ReadingUnits/AccelReadingUnit.ctl"/>
				<Item Name="GyroReadingUnit.ctl" Type="VI" URL="../FallSensor/ReadingUnits/GyroReadingUnit.ctl"/>
			</Item>
			<Item Name="QueueGUI" Type="Folder">
				<Item Name="GUIOperation.ctl" Type="VI" URL="../FallSensor/QueueGUI/GUIOperation.ctl"/>
				<Item Name="QueueGUIContext.ctl" Type="VI" URL="../FallSensor/QueueGUI/QueueGUIContext.ctl"/>
			</Item>
			<Item Name="FSContext.ctl" Type="VI" URL="../FallSensor/FSContext.ctl"/>
			<Item Name="FSState.ctl" Type="VI" URL="../FallSensor/FSState.ctl"/>
			<Item Name="Packet.ctl" Type="VI" URL="../FallSensor/Packet.ctl"/>
			<Item Name="Sample.ctl" Type="VI" URL="../FallSensor/Sample.ctl"/>
			<Item Name="Reading.ctl" Type="VI" URL="../FallSensor/Reading.ctl"/>
			<Item Name="DataType.ctl" Type="VI" URL="../FallSensor/DataType.ctl"/>
			<Item Name="EventStatus.ctl" Type="VI" URL="../FallSensor/EventStatus.ctl"/>
			<Item Name="GetPackets.vi" Type="VI" URL="../FallSensor/GetPackets.vi"/>
			<Item Name="SavePackets.vi" Type="VI" URL="../FallSensor/SavePackets.vi"/>
			<Item Name="LoadPackets.vi" Type="VI" URL="../FallSensor/LoadPackets.vi"/>
			<Item Name="EnqueueGUIUpdate.vi" Type="VI" URL="../FallSensor/EnqueueGUIUpdate.vi"/>
			<Item Name="DequeueGUIUpdate.vi" Type="VI" URL="../FallSensor/DequeueGUIUpdate.vi"/>
			<Item Name="EnqueueGUIMultipleUpdate.vi" Type="VI" URL="../FallSensor/EnqueueGUIMultipleUpdate.vi"/>
		</Item>
		<Item Name="Requests" Type="Folder">
			<Item Name="RequestType.ctl" Type="VI" URL="../Requests/RequestType.ctl"/>
			<Item Name="Request.ctl" Type="VI" URL="../Requests/Request.ctl"/>
			<Item Name="Requests.ctl" Type="VI" URL="../Requests/Requests.ctl"/>
			<Item Name="FindRequestByType.vi" Type="VI" URL="../Requests/FindRequestByType.vi"/>
		</Item>
		<Item Name="Frame" Type="Folder">
			<Item Name="DataFrame" Type="Folder">
				<Item Name="DataFrameContext.ctl" Type="VI" URL="../Frame/DataFrame/DataFrameContext.ctl"/>
				<Item Name="DataFrameSection.ctl" Type="VI" URL="../Frame/DataFrame/DataFrameSection.ctl"/>
				<Item Name="DataFrameSectionsLen.ctl" Type="VI" URL="../Frame/DataFrame/DataFrameSectionsLen.ctl"/>
				<Item Name="HexStringToSample.vi" Type="VI" URL="../Frame/DataFrame/HexStringToSample.vi"/>
				<Item Name="SampleToHexString.vi" Type="VI" URL="../Frame/DataFrame/SampleToHexString.vi"/>
				<Item Name="AppendNewPackets.vi" Type="VI" URL="../Frame/DataFrame/AppendNewPackets.vi"/>
				<Item Name="DetachNewPackets.vi" Type="VI" URL="../Frame/DataFrame/DetachNewPackets.vi"/>
			</Item>
			<Item Name="DecodeNumericFrame" Type="Folder">
				<Item Name="DNFContext.ctl" Type="VI" URL="../Frame/DecodeNumericFrame/DNFContext.ctl"/>
				<Item Name="DNFDataFrameSection.ctl" Type="VI" URL="../Frame/DecodeNumericFrame/DNFDataFrameSection.ctl"/>
				<Item Name="DNFDataFrameSectionsLen.ctl" Type="VI" URL="../Frame/DecodeNumericFrame/DNFDataFrameSectionsLen.ctl"/>
			</Item>
			<Item Name="DecodeFrameHeader.vi" Type="VI" URL="../Frame/DecodeFrameHeader.vi"/>
			<Item Name="DecodeNumericFrame.vi" Type="VI" URL="../Frame/DecodeNumericFrame.vi"/>
			<Item Name="DecodeNumericValue.vi" Type="VI" URL="../Frame/DecodeNumericValue.vi"/>
			<Item Name="DecodeDataFrame.vi" Type="VI" URL="../Frame/DecodeDataFrame.vi"/>
			<Item Name="EncodeFrameHeader.vi" Type="VI" URL="../Frame/EncodeFrameHeader.vi"/>
			<Item Name="EncodeNumericValue.vi" Type="VI" URL="../Frame/EncodeNumericValue.vi"/>
			<Item Name="EncodeDataFrame.vi" Type="VI" URL="../Frame/EncodeDataFrame.vi"/>
		</Item>
		<Item Name="FTDI" Type="Folder">
			<Item Name="COMConfigure.vi" Type="VI" URL="../FTDI/COMConfigure.vi"/>
			<Item Name="COMResponsiveness.ctl" Type="VI" URL="../FTDI/COMResponsiveness.ctl"/>
			<Item Name="COMConfig.ctl" Type="VI" URL="../FTDI/COMConfig.ctl"/>
			<Item Name="COMDirection.ctl" Type="VI" URL="../FTDI/COMDirection.ctl"/>
			<Item Name="COMMode.ctl" Type="VI" URL="../FTDI/COMMode.ctl"/>
			<Item Name="COMTransfer.vi" Type="VI" URL="../FTDI/COMTransfer.vi"/>
			<Item Name="FT_Get_COM_Port_Number.vi" Type="VI" URL="../FTDI/FT_Get_COM_Port_Number.vi"/>
			<Item Name="FT_Get_Device_Description_By_Index.vi" Type="VI" URL="../FTDI/FT_Get_Device_Description_By_Index.vi"/>
			<Item Name="FT_Open_Device_By_Description.vi" Type="VI" URL="../FTDI/FT_Open_Device_By_Description.vi"/>
			<Item Name="FT_Close_Device.vi" Type="VI" URL="../FTDI/FT_Close_Device.vi"/>
		</Item>
		<Item Name="File" Type="Folder">
			<Item Name="FormatData.vi" Type="VI" URL="../File/FormatData.vi"/>
			<Item Name="FormatDataContext.ctl" Type="VI" URL="../File/FormatDataContext.ctl"/>
			<Item Name="FileSection.ctl" Type="VI" URL="../File/FileSection.ctl"/>
			<Item Name="ScanData.vi" Type="VI" URL="../File/ScanData.vi"/>
		</Item>
		<Item Name="FallSensor.vi" Type="VI" URL="../FallSensor.vi"/>
		<Item Name="GetAvailableFTDevices.vi" Type="VI" URL="../GetAvailableFTDevices.vi"/>
		<Item Name="ProcessRequest.vi" Type="VI" URL="../ProcessRequest.vi"/>
		<Item Name="ScanDataContext.ctl" Type="VI" URL="../File/ScanDataContext.ctl"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="VISA Configure Serial Port (Serial Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Serial Instr).vi"/>
				<Item Name="VISA Configure Serial Port (Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Instr).vi"/>
				<Item Name="VISA Configure Serial Port" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port"/>
				<Item Name="RGB to Color.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/colorconv.llb/RGB to Color.vi"/>
				<Item Name="Application Directory.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Application Directory.vi"/>
				<Item Name="NI_FileType.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/lvfile.llb/NI_FileType.lvlib"/>
				<Item Name="Error Cluster From Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Cluster From Error Code.vi"/>
				<Item Name="ex_CorrectErrorChain.vi" Type="VI" URL="/&lt;vilib&gt;/express/express shared/ex_CorrectErrorChain.vi"/>
				<Item Name="subFile Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/express/express input/FileDialogBlock.llb/subFile Dialog.vi"/>
				<Item Name="GetHelpDir.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetHelpDir.vi"/>
				<Item Name="BuildHelpPath.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/BuildHelpPath.vi"/>
				<Item Name="LVBoundsTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVBoundsTypeDef.ctl"/>
				<Item Name="Get String Text Bounds.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Get String Text Bounds.vi"/>
				<Item Name="Get Text Rect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Get Text Rect.vi"/>
				<Item Name="Convert property node font to graphics font.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Convert property node font to graphics font.vi"/>
				<Item Name="Longest Line Length in Pixels.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Longest Line Length in Pixels.vi"/>
				<Item Name="LVRectTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVRectTypeDef.ctl"/>
				<Item Name="Three Button Dialog CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog CORE.vi"/>
				<Item Name="Three Button Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog.vi"/>
				<Item Name="DialogTypeEnum.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogTypeEnum.ctl"/>
				<Item Name="Not Found Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Not Found Dialog.vi"/>
				<Item Name="Set Bold Text.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set Bold Text.vi"/>
				<Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
				<Item Name="eventvkey.ctl" Type="VI" URL="/&lt;vilib&gt;/event_ctls.llb/eventvkey.ctl"/>
				<Item Name="TagReturnType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/TagReturnType.ctl"/>
				<Item Name="ErrWarn.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/ErrWarn.ctl"/>
				<Item Name="Details Display Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Details Display Dialog.vi"/>
				<Item Name="Search and Replace Pattern.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Search and Replace Pattern.vi"/>
				<Item Name="Find Tag.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Find Tag.vi"/>
				<Item Name="Format Message String.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Format Message String.vi"/>
				<Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
				<Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
				<Item Name="Error Code Database.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Code Database.vi"/>
				<Item Name="GetRTHostConnectedProp.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetRTHostConnectedProp.vi"/>
				<Item Name="Set String Value.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set String Value.vi"/>
				<Item Name="Check Special Tags.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Check Special Tags.vi"/>
				<Item Name="General Error Handler Core CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler Core CORE.vi"/>
				<Item Name="DialogType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogType.ctl"/>
				<Item Name="General Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler.vi"/>
				<Item Name="Simple Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Simple Error Handler.vi"/>
			</Item>
			<Item Name="FTD2XX.dll" Type="Document" URL="FTD2XX.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
		</Item>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
