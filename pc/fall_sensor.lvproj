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
			<Item Name="QueueGUI" Type="Folder">
				<Item Name="GUIOperation.ctl" Type="VI" URL="../FallSensor/QueueGUI/GUIOperation.ctl"/>
				<Item Name="QueueGUIContext.ctl" Type="VI" URL="../FallSensor/QueueGUI/QueueGUIContext.ctl"/>
			</Item>
			<Item Name="Measurement" Type="Folder">
				<Item Name="AccelFSRange.ctl" Type="VI" URL="../FallSensor/Measurement/AccelFSRange.ctl"/>
				<Item Name="GyroFSRange.ctl" Type="VI" URL="../FallSensor/Measurement/GyroFSRange.ctl"/>
				<Item Name="MeasSample.ctl" Type="VI" URL="../FallSensor/Measurement/MeasSample.ctl"/>
				<Item Name="MeasReading.ctl" Type="VI" URL="../FallSensor/Measurement/MeasReading.ctl"/>
				<Item Name="ConvertSamples.vi" Type="VI" URL="../FallSensor/Measurement/ConvertSamples.vi"/>
				<Item Name="AccelFSRangeToDouble.vi" Type="VI" URL="../FallSensor/Measurement/AccelFSRangeToDouble.vi"/>
				<Item Name="GyroFSRangeToDouble.vi" Type="VI" URL="../FallSensor/Measurement/GyroFSRangeToDouble.vi"/>
			</Item>
			<Item Name="ExportPacket" Type="Folder">
				<Item Name="ExportPacketToCSV.vi" Type="VI" URL="../FallSensor/ExportPacket/ExportPacketToCSV.vi"/>
				<Item Name="ExportPacketToJSON.vi" Type="VI" URL="../FallSensor/ExportPacket/ExportPacketToJSON.vi"/>
				<Item Name="ExportType.ctl" Type="VI" URL="../FallSensor/ExportPacket/ExportType.ctl"/>
			</Item>
			<Item Name="ConfigureDevice" Type="Folder">
				<Item Name="CDContext.ctl" Type="VI" URL="../FallSensor/ConfigureDevice/CDContext.ctl"/>
				<Item Name="CDState.ctl" Type="VI" URL="../FallSensor/ConfigureDevice/CDState.ctl"/>
				<Item Name="CDAccelFSRange.ctl" Type="VI" URL="../FallSensor/ConfigureDevice/CDAccelFSRange.ctl"/>
				<Item Name="CDGyroFSRange.ctl" Type="VI" URL="../FallSensor/ConfigureDevice/CDGyroFSRange.ctl"/>
				<Item Name="CDOutputDataRate.ctl" Type="VI" URL="../FallSensor/ConfigureDevice/CDOutputDataRate.ctl"/>
				<Item Name="CDAccelDLPF.ctl" Type="VI" URL="../FallSensor/ConfigureDevice/CDAccelDLPF.ctl"/>
				<Item Name="CDGyroDLPF.ctl" Type="VI" URL="../FallSensor/ConfigureDevice/CDGyroDLPF.ctl"/>
				<Item Name="CDInterruptPinMode.ctl" Type="VI" URL="../FallSensor/ConfigureDevice/CDInterruptPinMode.ctl"/>
				<Item Name="CDInterruptMode.ctl" Type="VI" URL="../FallSensor/ConfigureDevice/CDInterruptMode.ctl"/>
				<Item Name="CDSensorConfiguration.ctl" Type="VI" URL="../FallSensor/ConfigureDevice/CDSensorConfiguration.ctl"/>
			</Item>
			<Item Name="FSContext.ctl" Type="VI" URL="../FallSensor/FSContext.ctl"/>
			<Item Name="FSState.ctl" Type="VI" URL="../FallSensor/FSState.ctl"/>
			<Item Name="Packet.ctl" Type="VI" URL="../FallSensor/Packet.ctl"/>
			<Item Name="Sample.ctl" Type="VI" URL="../FallSensor/Sample.ctl"/>
			<Item Name="Reading.ctl" Type="VI" URL="../FallSensor/Reading.ctl"/>
			<Item Name="DataType.ctl" Type="VI" URL="../FallSensor/DataType.ctl"/>
			<Item Name="EventStatus.ctl" Type="VI" URL="../FallSensor/EventStatus.ctl"/>
			<Item Name="MeasurementConfig.ctl" Type="VI" URL="../FallSensor/MeasurementConfig.ctl"/>
			<Item Name="AlignStringWithSpaces.vi" Type="VI" URL="../FallSensor/AlignStringWithSpaces.vi"/>
			<Item Name="ConfigureDevice.vi" Type="VI" URL="../FallSensor/ConfigureDevice.vi"/>
			<Item Name="GetPackets.vi" Type="VI" URL="../FallSensor/GetPackets.vi"/>
			<Item Name="SavePackets.vi" Type="VI" URL="../FallSensor/SavePackets.vi"/>
			<Item Name="LoadPackets.vi" Type="VI" URL="../FallSensor/LoadPackets.vi"/>
			<Item Name="ExportPacket.vi" Type="VI" URL="../FallSensor/ExportPacket.vi"/>
			<Item Name="EditComment.vi" Type="VI" URL="../FallSensor/EditComment.vi"/>
			<Item Name="TakeGraphsScreenshot.vi" Type="VI" URL="../FallSensor/TakeGraphsScreenshot.vi"/>
			<Item Name="EnqueueGUIUpdate.vi" Type="VI" URL="../FallSensor/EnqueueGUIUpdate.vi"/>
			<Item Name="DequeueGUIUpdate.vi" Type="VI" URL="../FallSensor/DequeueGUIUpdate.vi"/>
			<Item Name="EnqueueGUIMultipleUpdate.vi" Type="VI" URL="../FallSensor/EnqueueGUIMultipleUpdate.vi"/>
			<Item Name="MenuTags.ctl" Type="VI" URL="../FallSensor/MenuTags.ctl"/>
			<Item Name="Menu.rtm" Type="Document" URL="../FallSensor/Menu.rtm"/>
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
			<Item Name="FileContent.ctl" Type="VI" URL="../File/FileContent.ctl"/>
			<Item Name="FormatData.vi" Type="VI" URL="../File/FormatData.vi"/>
			<Item Name="ScanData.vi" Type="VI" URL="../File/ScanData.vi"/>
		</Item>
		<Item Name="JSON" Type="Folder">
			<Item Name="JSONStreamType.ctl" Type="VI" URL="../JSON/JSONStreamType.ctl"/>
			<Item Name="JSONToSensorConfig.vi" Type="VI" URL="../JSON/JSONToSensorConfig.vi"/>
			<Item Name="Measurement6DoFToJSON.vi" Type="VI" URL="../JSON/Measurement6DoFToJSON.vi"/>
			<Item Name="SensorConfigToJSON.vi" Type="VI" URL="../JSON/SensorConfigToJSON.vi"/>
		</Item>
		<Item Name="FallSensor.vi" Type="VI" URL="../FallSensor.vi"/>
		<Item Name="GetAvailableFTDevices.vi" Type="VI" URL="../GetAvailableFTDevices.vi"/>
		<Item Name="ProcessRequest.vi" Type="VI" URL="../ProcessRequest.vi"/>
		<Item Name="fall_sensor_icon.ico" Type="Document" URL="../fall_sensor_icon.ico"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="VISA Configure Serial Port (Serial Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Serial Instr).vi"/>
				<Item Name="VISA Configure Serial Port (Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Instr).vi"/>
				<Item Name="VISA Configure Serial Port" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port"/>
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
				<Item Name="LVRowAndColumnUnsignedTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVRowAndColumnUnsignedTypeDef.ctl"/>
				<Item Name="JSON Object.lvclass" Type="LVClass" URL="/&lt;vilib&gt;/addons/JSON API/JSON Object/JSON Object.lvclass"/>
				<Item Name="JSON Value.lvclass" Type="LVClass" URL="/&lt;vilib&gt;/addons/JSON API/JSON Value/JSON Value.lvclass"/>
				<Item Name="JSON Scalar.lvclass" Type="LVClass" URL="/&lt;vilib&gt;/addons/JSON API/JSON Scalar/JSON Scalar.lvclass"/>
				<Item Name="JSON support.lvlib" Type="Library" URL="/&lt;vilib&gt;/addons/JSON API/support/JSON support.lvlib"/>
				<Item Name="VariantType.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/VariantDataType/VariantType.lvlib"/>
				<Item Name="TD_Refnum Kind.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/GetType.llb/TD_Refnum Kind.ctl"/>
				<Item Name="Type Descriptor I16.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/GetType.llb/Type Descriptor I16.ctl"/>
				<Item Name="Type Descriptor I16 Array.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/GetType.llb/Type Descriptor I16 Array.ctl"/>
				<Item Name="TD_Get Ref Info.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/GetType.llb/TD_Get Ref Info.vi"/>
				<Item Name="Type Code.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/GetType.llb/Type Code.ctl"/>
				<Item Name="Type Enum.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/GetType.llb/Type Enum.ctl"/>
				<Item Name="Get Type Code from I16 Array And Pos.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/GetType.llb/Get Type Code from I16 Array And Pos.vi"/>
				<Item Name="JSON Statistics.lvclass" Type="LVClass" URL="/&lt;vilib&gt;/addons/JSON API/Statistics/JSON Statistics.lvclass"/>
				<Item Name="NI_AALBase.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/NI_AALBase.lvlib"/>
				<Item Name="JSON Running Mean.lvclass" Type="LVClass" URL="/&lt;vilib&gt;/addons/JSON API/JSON Running Mean/JSON Running Mean.lvclass"/>
				<Item Name="JSON Array.lvclass" Type="LVClass" URL="/&lt;vilib&gt;/addons/JSON API/JSON Array/JSON Array.lvclass"/>
				<Item Name="TD_GetPStr.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/GetType.llb/TD_GetPStr.vi"/>
				<Item Name="TD_Get Enum Information.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/GetType.llb/TD_Get Enum Information.vi"/>
				<Item Name="Variant JSON.lvlib" Type="Library" URL="/&lt;vilib&gt;/addons/JSON API/Variant JSON/Variant JSON.lvlib"/>
				<Item Name="JSON GetSet.lvlib" Type="Library" URL="/&lt;vilib&gt;/addons/JSON API/Get Polymorphic/JSON GetSet.lvlib"/>
				<Item Name="Write Delimited Spreadsheet.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Write Delimited Spreadsheet.vi"/>
				<Item Name="Write Delimited Spreadsheet (DBL).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Write Delimited Spreadsheet (DBL).vi"/>
				<Item Name="Write Spreadsheet String.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Write Spreadsheet String.vi"/>
				<Item Name="Write Delimited Spreadsheet (I64).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Write Delimited Spreadsheet (I64).vi"/>
				<Item Name="Write Delimited Spreadsheet (string).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Write Delimited Spreadsheet (string).vi"/>
				<Item Name="Check Data Size.vi" Type="VI" URL="/&lt;vilib&gt;/picture/jpeg.llb/Check Data Size.vi"/>
				<Item Name="Check Color Table Size.vi" Type="VI" URL="/&lt;vilib&gt;/picture/jpeg.llb/Check Color Table Size.vi"/>
				<Item Name="Directory of Top Level VI.vi" Type="VI" URL="/&lt;vilib&gt;/picture/jpeg.llb/Directory of Top Level VI.vi"/>
				<Item Name="Check Path.vi" Type="VI" URL="/&lt;vilib&gt;/picture/jpeg.llb/Check Path.vi"/>
				<Item Name="Check File Permissions.vi" Type="VI" URL="/&lt;vilib&gt;/picture/jpeg.llb/Check File Permissions.vi"/>
				<Item Name="imagedata.ctl" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/imagedata.ctl"/>
				<Item Name="Write PNG File.vi" Type="VI" URL="/&lt;vilib&gt;/picture/png.llb/Write PNG File.vi"/>
				<Item Name="NI_PackedLibraryUtility.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/LVLibp/NI_PackedLibraryUtility.lvlib"/>
				<Item Name="Check if File or Folder Exists.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/Check if File or Folder Exists.vi"/>
			</Item>
			<Item Name="user.lib" Type="Folder">
				<Item Name="Get PString__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get PString__ogtk.vi"/>
				<Item Name="Build Error Cluster__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/error/error.llb/Build Error Cluster__ogtk.vi"/>
				<Item Name="Type Descriptor Enumeration__ogtk.ctl" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Type Descriptor Enumeration__ogtk.ctl"/>
				<Item Name="Type Descriptor Header__ogtk.ctl" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Type Descriptor Header__ogtk.ctl"/>
				<Item Name="Type Descriptor__ogtk.ctl" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Type Descriptor__ogtk.ctl"/>
				<Item Name="Get Header from TD__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get Header from TD__ogtk.vi"/>
				<Item Name="Get Strings from Enum TD__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get Strings from Enum TD__ogtk.vi"/>
				<Item Name="Variant to Header Info__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Variant to Header Info__ogtk.vi"/>
				<Item Name="Get Strings from Enum__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get Strings from Enum__ogtk.vi"/>
				<Item Name="Get Last PString__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get Last PString__ogtk.vi"/>
				<Item Name="Get Variant Attributes__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get Variant Attributes__ogtk.vi"/>
				<Item Name="Set Data Name__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Set Data Name__ogtk.vi"/>
				<Item Name="Array of VData to VCluster__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Array of VData to VCluster__ogtk.vi"/>
				<Item Name="Split Cluster TD__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Split Cluster TD__ogtk.vi"/>
				<Item Name="Get Data Name from TD__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get Data Name from TD__ogtk.vi"/>
				<Item Name="Waveform Subtype Enum__ogtk.ctl" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Waveform Subtype Enum__ogtk.ctl"/>
				<Item Name="Get Waveform Type Enum from TD__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get Waveform Type Enum from TD__ogtk.vi"/>
				<Item Name="Get Default Data from TD__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get Default Data from TD__ogtk.vi"/>
				<Item Name="Get Default Data from Variant__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get Default Data from Variant__ogtk.vi"/>
				<Item Name="Get Data Name__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get Data Name__ogtk.vi"/>
				<Item Name="Get Element TD from Array TD__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get Element TD from Array TD__ogtk.vi"/>
				<Item Name="Get Array Element TD__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get Array Element TD__ogtk.vi"/>
				<Item Name="Reshape 1D Array__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Reshape 1D Array__ogtk.vi"/>
				<Item Name="Get TDEnum from Data__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Get TDEnum from Data__ogtk.vi"/>
				<Item Name="Array of VData to VArray__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Array of VData to VArray__ogtk.vi"/>
				<Item Name="Set Enum String Value__ogtk.vi" Type="VI" URL="/&lt;userlib&gt;/_OpenG.lib/lvdata/lvdata.llb/Set Enum String Value__ogtk.vi"/>
			</Item>
			<Item Name="FTD2XX.dll" Type="Document" URL="FTD2XX.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
		</Item>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="FallSensor" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{FC2500DD-1396-4BFC-AD54-F58A83A3872B}</Property>
				<Property Name="App_INI_GUID" Type="Str">{EEF77B20-600C-40C7-9686-54D2622FC3D9}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{6CB45967-7D97-4B82-B531-2C2908F571B6}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">FallSensor</Property>
				<Property Name="Bld_excludeInlineSubVIs" Type="Bool">true</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../builds/NI_AB_PROJECTNAME/FallSensor</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{FB715B9E-2340-402D-A8E2-60AD6A76F66B}</Property>
				<Property Name="Bld_version.minor" Type="Int">9</Property>
				<Property Name="Destination[0].destName" Type="Str">FallSensor.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../builds/NI_AB_PROJECTNAME/FallSensor/FallSensor.exe</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../builds/NI_AB_PROJECTNAME/FallSensor/data</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Exe_iconItemID" Type="Ref">/My Computer/fall_sensor_icon.ico</Property>
				<Property Name="Source[0].itemID" Type="Str">{DEB3932D-59E0-423E-B7A5-727E621449F2}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/FallSensor.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="Source[2].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[2].itemID" Type="Ref">/My Computer/FallSensor/ConfigureDevice.vi</Property>
				<Property Name="Source[2].type" Type="Str">VI</Property>
				<Property Name="Source[3].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[3].itemID" Type="Ref">/My Computer/FallSensor/GetPackets.vi</Property>
				<Property Name="Source[3].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">4</Property>
				<Property Name="TgtF_internalName" Type="Str">FallSensor</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2017 Lukasz Marcul</Property>
				<Property Name="TgtF_productName" Type="Str">FallSensor</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{98A68A54-73B2-4E3F-B451-4003C08281C9}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">FallSensor.exe</Property>
			</Item>
		</Item>
	</Item>
</Project>
