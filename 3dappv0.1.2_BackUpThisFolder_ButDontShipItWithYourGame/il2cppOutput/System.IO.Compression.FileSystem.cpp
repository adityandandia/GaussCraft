#include "pch-cpp.hpp"





template <typename T1, typename T2>
struct VirtualActionInvoker2
{
	typedef void (*Action)(void*, T1, T2, const RuntimeMethod*);

	static inline void Invoke (Il2CppMethodSlot slot, RuntimeObject* obj, T1 p1, T2 p2)
	{
		const VirtualInvokeData& invokeData = il2cpp_codegen_get_virtual_invoke_data(slot, obj);
		((Action)invokeData.methodPtr)(obj, p1, p2, invokeData.method);
	}
};
template <typename R>
struct VirtualFuncInvoker0
{
	typedef R (*Func)(void*, const RuntimeMethod*);

	static inline R Invoke (Il2CppMethodSlot slot, RuntimeObject* obj)
	{
		const VirtualInvokeData& invokeData = il2cpp_codegen_get_virtual_invoke_data(slot, obj);
		return ((Func)invokeData.methodPtr)(obj, invokeData.method);
	}
};
template <typename R, typename T1>
struct VirtualFuncInvoker1
{
	typedef R (*Func)(void*, T1, const RuntimeMethod*);

	static inline R Invoke (Il2CppMethodSlot slot, RuntimeObject* obj, T1 p1)
	{
		const VirtualInvokeData& invokeData = il2cpp_codegen_get_virtual_invoke_data(slot, obj);
		return ((Func)invokeData.methodPtr)(obj, p1, invokeData.method);
	}
};
struct InterfaceActionInvoker0
{
	typedef void (*Action)(void*, const RuntimeMethod*);

	static inline void Invoke (Il2CppMethodSlot slot, RuntimeClass* declaringInterface, RuntimeObject* obj)
	{
		const VirtualInvokeData& invokeData = il2cpp_codegen_get_interface_invoke_data(slot, obj, declaringInterface);
		((Action)invokeData.methodPtr)(obj, invokeData.method);
	}
};
template <typename R>
struct InterfaceFuncInvoker0
{
	typedef R (*Func)(void*, const RuntimeMethod*);

	static inline R Invoke (Il2CppMethodSlot slot, RuntimeClass* declaringInterface, RuntimeObject* obj)
	{
		const VirtualInvokeData& invokeData = il2cpp_codegen_get_interface_invoke_data(slot, obj, declaringInterface);
		return ((Func)invokeData.methodPtr)(obj, invokeData.method);
	}
};

struct ArrayPool_1_t3CE8332C9DFE03FF160AB0CE0FF17DF7792E0E4B;
struct Dictionary_2_t87EDE08B2E48F793A22DE50D6B3CC2E7EBB2DB54;
struct Dictionary_2_tA1C10CF9D35962FF0289095A43DEE774B7F13C47;
struct IEnumerable_1_t8D7AC720F84EFB74460403413F0F6BE54649BAF0;
struct IEnumerable_1_t349E66EC5F09B881A8E52EE40A1AB9EC60E08E44;
struct IEnumerator_1_tB2588994D1BF27F8465E01E530B6EC04F04ED369;
struct IEnumerator_1_t73FD060C436E3C4264A734C8F8DCC01DFF6046B8;
struct List_1_tA389B1109F43128C89C6358C6B56C819460CF5B3;
struct List_1_t0845A5AAFB6B816C6E2719A0588604CE3A080FDC;
struct ReadOnlyCollection_1_t15A54E961DBC027444DA89894B8AD689A38CE9AC;
struct ByteU5BU5DU5BU5D_t19A0C6D66F22DF673E9CDB37DEF566FE0EC947FA;
struct ByteU5BU5D_tA6237BF417AE52AD70CFB4EF24A7A82613DF9031;
struct CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB;
struct Int32U5BU5D_t19C97395396A72ECAF310612F0760F165060314C;
struct IntPtrU5BU5D_tFD177F8C806A6921AD7150264CCC62FA00CAD832;
struct StackTraceU5BU5D_t32FBCB20930EAF5BAE3F450FF75228E5450DA0DF;
struct ArgumentNullException_t327031E412FAB2351B0022DD5DAD47E67E597129;
struct ArgumentOutOfRangeException_tEA2822DAF62B10EEED00E0E3A341D4BAF78CF85F;
struct BinaryReader_t9A6D85F0FE9AE4EBB5E8D66997DFD1D84939E158;
struct CodePageDataItem_t52460FA30AE37F4F26ACB81055E58002262F19F2;
struct DecoderFallback_t7324102215E4ED41EC065C02EB501CB0BC23CD90;
struct DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2;
struct EncoderFallback_tD2C40CE114AA9D8E1F7196608B2D088548015293;
struct Encoding_t65CDEF28CF20A7B8C92E85A4E808920C2465F095;
struct FileStream_t07C7222EE10B75F352B89B76E60820160FF10AD8;
struct FileSystemInfo_tE3063B9229F46B05A5F6D018C8C4CA510104E8E9;
struct IDictionary_t6D03155AF1FA9083817AA5B6AD7DEEACC26AB220;
struct MemoryStream_tAAED1B42172E3390584E4194308AB878E786AAC2;
struct SafeFileHandle_t033FA6AAAC65F4BB25F4CBA9A242A58C95CD406E;
struct SafeSerializationManager_tCBB85B95DFD1634237140CD892E82D06ECB3F5E6;
struct SemaphoreSlim_t0D5CB5685D9BFA5BF95CEC6E7395490F933E8DB2;
struct Stream_tF844051B786E8F7F4244DBD218D74E8617B9A2DE;
struct String_t;
struct Void_t4861ACF8F4594C3437BB48B6E56783494B843915;
struct ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41;
struct ZipArchiveEntry_tEFD75A0570102F8A3DF70A038302146B46071DD4;
struct ReadWriteTask_t0821BF49EE38596C7734E86E1A6A39D769BE2C05;

IL2CPP_EXTERN_C RuntimeClass* ArgumentNullException_t327031E412FAB2351B0022DD5DAD47E67E597129_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* ArgumentOutOfRangeException_tEA2822DAF62B10EEED00E0E3A341D4BAF78CF85F_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* ArrayPool_1_t3CE8332C9DFE03FF160AB0CE0FF17DF7792E0E4B_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* DateTimeOffset_t4EE701FE2F386D6F932FAC9B11E4B74A5B30F0A4_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* DateTime_t66193957C73913903DDAD89FEDC46139BCA5802D_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* FileInfo_t62782BBAFA832A78724E4CF2EE96548B8466AB1C_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* FileStream_t07C7222EE10B75F352B89B76E60820160FF10AD8_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* IDisposable_t030E0496B4E0E4E4F086825007979AF51F7248C5_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* IEnumerable_1_t349E66EC5F09B881A8E52EE40A1AB9EC60E08E44_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* IEnumerable_1_t8D7AC720F84EFB74460403413F0F6BE54649BAF0_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* IEnumerator_1_tB2588994D1BF27F8465E01E530B6EC04F04ED369_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* IEnumerator_t7B609C2FFA6EB5167D9C62A0C32A21DE2F666DAA_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* Path_t8A38A801D0219E8209C1B1D90D82D4D755D998BC_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C String_t* _stringLiteral56F96CA2C7CD86A940882DB30231478A10E0B61F;
IL2CPP_EXTERN_C String_t* _stringLiteralAF248E82BE9EBA1ADBF067429FAEE5A5B6E05A74;
IL2CPP_EXTERN_C String_t* _stringLiteralD89ADD2DB1FBF30630EEA02FAAF144060CA0E908;
IL2CPP_EXTERN_C String_t* _stringLiteralE280D065A824A791F8305234D3E093FC9A5A90C7;
IL2CPP_EXTERN_C String_t* _stringLiteralEC39AAB8B28BCEDAFA6F3285CC603CE852769989;
IL2CPP_EXTERN_C const RuntimeMethod* ArrayPool_1_get_Shared_m8EB88B4EDF81135B55DB0F33A749B8087FE4646F_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* Nullable_1_get_HasValue_mEBB6F9CB853B438D075BB555958691054B188001_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* Nullable_1_get_Value_mE771FFC5C0CA05BC9996418326C1D36E8A33DB2A_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* ZipFileExtensions_DoCreateEntryFromFile_m0B0768102927FBBB004A43ECE057BE6680B91F26_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* ZipFile_Open_m6F83ACFED32799E052503C5CEAE6DD0D145FCC8D_RuntimeMethod_var;
struct Exception_t_marshaled_com;
struct Exception_t_marshaled_pinvoke;

struct CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB;

IL2CPP_EXTERN_C_BEGIN
IL2CPP_EXTERN_C_END

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
struct U3CModuleU3E_t5C9D30A33D5BCEBCEE3B70E895505EE5A827FE73 
{
};
struct ArrayPool_1_t3CE8332C9DFE03FF160AB0CE0FF17DF7792E0E4B  : public RuntimeObject
{
};
struct Encoding_t65CDEF28CF20A7B8C92E85A4E808920C2465F095  : public RuntimeObject
{
	int32_t ___m_codePage;
	CodePageDataItem_t52460FA30AE37F4F26ACB81055E58002262F19F2* ___dataItem;
	bool ___m_deserializedFromEverett;
	bool ___m_isReadOnly;
	EncoderFallback_tD2C40CE114AA9D8E1F7196608B2D088548015293* ___encoderFallback;
	DecoderFallback_t7324102215E4ED41EC065C02EB501CB0BC23CD90* ___decoderFallback;
};
struct MarshalByRefObject_t8C2F4C5854177FD60439EB1FCCFC1B3CFAFE8DCE  : public RuntimeObject
{
	RuntimeObject* ____identity;
};
struct MarshalByRefObject_t8C2F4C5854177FD60439EB1FCCFC1B3CFAFE8DCE_marshaled_pinvoke
{
	Il2CppIUnknown* ____identity;
};
struct MarshalByRefObject_t8C2F4C5854177FD60439EB1FCCFC1B3CFAFE8DCE_marshaled_com
{
	Il2CppIUnknown* ____identity;
};
struct Path_t8A38A801D0219E8209C1B1D90D82D4D755D998BC  : public RuntimeObject
{
};
struct String_t  : public RuntimeObject
{
	int32_t ____stringLength;
	Il2CppChar ____firstChar;
};
struct ValueType_t6D9B272BD21782F0A9A14F2E41F85A50E97A986F  : public RuntimeObject
{
};
struct ValueType_t6D9B272BD21782F0A9A14F2E41F85A50E97A986F_marshaled_pinvoke
{
};
struct ValueType_t6D9B272BD21782F0A9A14F2E41F85A50E97A986F_marshaled_com
{
};
struct ZipFile_t18C9C6BB8ABF9F2AE85A0EB6FF918378A5745CC8  : public RuntimeObject
{
};
struct ZipFileExtensions_t06E75DEE7D8E222C1E0E563C2393652E251FD218  : public RuntimeObject
{
};
struct Nullable_1_t365991B3904FDA7642A788423B28692FDC7CDB17 
{
	bool ___hasValue;
	int64_t ___value;
};
struct Boolean_t09A6377A54BE2F9E6985A8149F19234FD7DDFE22 
{
	bool ___m_value;
};
struct Char_t521A6F19B456D956AF452D926C32709DC03D6B17 
{
	Il2CppChar ___m_value;
};
struct DateTime_t66193957C73913903DDAD89FEDC46139BCA5802D 
{
	uint64_t ____dateData;
};
struct Enum_t2A1A94B24E3B776EEF4E5E485E290BB9D4D072E2  : public ValueType_t6D9B272BD21782F0A9A14F2E41F85A50E97A986F
{
};
struct Enum_t2A1A94B24E3B776EEF4E5E485E290BB9D4D072E2_marshaled_pinvoke
{
};
struct Enum_t2A1A94B24E3B776EEF4E5E485E290BB9D4D072E2_marshaled_com
{
};
struct Int32_t680FF22E76F6EFAD4375103CBBFFA0421349384C 
{
	int32_t ___m_value;
};
struct IntPtr_t 
{
	void* ___m_value;
};
struct Stream_tF844051B786E8F7F4244DBD218D74E8617B9A2DE  : public MarshalByRefObject_t8C2F4C5854177FD60439EB1FCCFC1B3CFAFE8DCE
{
	ReadWriteTask_t0821BF49EE38596C7734E86E1A6A39D769BE2C05* ____activeReadWriteTask;
	SemaphoreSlim_t0D5CB5685D9BFA5BF95CEC6E7395490F933E8DB2* ____asyncActiveSemaphore;
};
struct Void_t4861ACF8F4594C3437BB48B6E56783494B843915 
{
	union
	{
		struct
		{
		};
		uint8_t Void_t4861ACF8F4594C3437BB48B6E56783494B843915__padding[1];
	};
};
struct CompressionLevel_t6077A887918BD6DACDD8D3F0D660D157A604B1E1 
{
	int32_t ___value__;
};
struct DateTimeOffset_t4EE701FE2F386D6F932FAC9B11E4B74A5B30F0A4 
{
	DateTime_t66193957C73913903DDAD89FEDC46139BCA5802D ____dateTime;
	int16_t ____offsetMinutes;
};
struct Exception_t  : public RuntimeObject
{
	String_t* ____className;
	String_t* ____message;
	RuntimeObject* ____data;
	Exception_t* ____innerException;
	String_t* ____helpURL;
	RuntimeObject* ____stackTrace;
	String_t* ____stackTraceString;
	String_t* ____remoteStackTraceString;
	int32_t ____remoteStackIndex;
	RuntimeObject* ____dynamicMethods;
	int32_t ____HResult;
	String_t* ____source;
	SafeSerializationManager_tCBB85B95DFD1634237140CD892E82D06ECB3F5E6* ____safeSerializationManager;
	StackTraceU5BU5D_t32FBCB20930EAF5BAE3F450FF75228E5450DA0DF* ___captured_traces;
	IntPtrU5BU5D_tFD177F8C806A6921AD7150264CCC62FA00CAD832* ___native_trace_ips;
	int32_t ___caught_in_unmanaged;
};
struct Exception_t_marshaled_pinvoke
{
	char* ____className;
	char* ____message;
	RuntimeObject* ____data;
	Exception_t_marshaled_pinvoke* ____innerException;
	char* ____helpURL;
	Il2CppIUnknown* ____stackTrace;
	char* ____stackTraceString;
	char* ____remoteStackTraceString;
	int32_t ____remoteStackIndex;
	Il2CppIUnknown* ____dynamicMethods;
	int32_t ____HResult;
	char* ____source;
	SafeSerializationManager_tCBB85B95DFD1634237140CD892E82D06ECB3F5E6* ____safeSerializationManager;
	StackTraceU5BU5D_t32FBCB20930EAF5BAE3F450FF75228E5450DA0DF* ___captured_traces;
	Il2CppSafeArray* ___native_trace_ips;
	int32_t ___caught_in_unmanaged;
};
struct Exception_t_marshaled_com
{
	Il2CppChar* ____className;
	Il2CppChar* ____message;
	RuntimeObject* ____data;
	Exception_t_marshaled_com* ____innerException;
	Il2CppChar* ____helpURL;
	Il2CppIUnknown* ____stackTrace;
	Il2CppChar* ____stackTraceString;
	Il2CppChar* ____remoteStackTraceString;
	int32_t ____remoteStackIndex;
	Il2CppIUnknown* ____dynamicMethods;
	int32_t ____HResult;
	Il2CppChar* ____source;
	SafeSerializationManager_tCBB85B95DFD1634237140CD892E82D06ECB3F5E6* ____safeSerializationManager;
	StackTraceU5BU5D_t32FBCB20930EAF5BAE3F450FF75228E5450DA0DF* ___captured_traces;
	Il2CppSafeArray* ___native_trace_ips;
	int32_t ___caught_in_unmanaged;
};
struct FileAccess_t3992FF4CCC61971B804DD291F06F696C3CF33C30 
{
	int32_t ___value__;
};
struct FileMode_t111B48D5347628AEFCBF9A0EC2833827A302ECBA 
{
	int32_t ___value__;
};
struct FileShare_t0A0E9739F5AB44D6B8026C9D2A2F1CEEE442733A 
{
	int32_t ___value__;
};
struct Int32Enum_tCBAC8BA2BFF3A845FA599F303093BBBA374B6F0C 
{
	int32_t ___value__;
};
struct SearchOption_tDCBB43E1597F64296592F64A1E685996A57EA392 
{
	int32_t ___value__;
};
struct ZipArchiveMode_tD0AA40EAC5C26DBB24E9F4AA965A0C83AB003BCD 
{
	int32_t ___value__;
};
struct ZipVersionMadeByPlatform_t0188CEF15A70E487DF8FEF967B9C70FE536330BE 
{
	uint8_t ___value__;
};
struct ZipVersionNeededValues_tA5A8C9E6B35A8273F2C0272F71053147EA4F0F5C 
{
	uint16_t ___value__;
};
struct BitFlagValues_tF0EF994D25EEFFA919B1774684312A68792BE372 
{
	uint16_t ___value__;
};
struct CompressionMethodValues_tC8C0E4F84E6CBF8501427A5A0CE2261859636BDC 
{
	uint16_t ___value__;
};
struct FileStatusFlags_tB53E2B9A54305CDCEA49884DEEDB8C62C8ACC9C9 
{
	int32_t ___value__;
};
struct Nullable_1_tAC8899D7718BEF36A8590184EFBCA842A1BC9AB1 
{
	bool ___hasValue;
	int32_t ___value;
};
struct Nullable_1_t163D49A1147F217B7BD43BE8ACC8A5CC6B846D14 
{
	bool ___hasValue;
	int32_t ___value;
};
struct FileStream_t07C7222EE10B75F352B89B76E60820160FF10AD8  : public Stream_tF844051B786E8F7F4244DBD218D74E8617B9A2DE
{
	ByteU5BU5D_tA6237BF417AE52AD70CFB4EF24A7A82613DF9031* ___buf;
	String_t* ___name;
	SafeFileHandle_t033FA6AAAC65F4BB25F4CBA9A242A58C95CD406E* ___safeHandle;
	bool ___isExposed;
	int64_t ___append_startpos;
	int32_t ___access;
	bool ___owner;
	bool ___async;
	bool ___canseek;
	bool ___anonymous;
	bool ___buf_dirty;
	int32_t ___buf_size;
	int32_t ___buf_length;
	int32_t ___buf_offset;
	int64_t ___buf_start;
};
struct SystemException_tCC48D868298F4C0705279823E34B00F4FBDB7295  : public Exception_t
{
};
struct ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41  : public RuntimeObject
{
	Stream_tF844051B786E8F7F4244DBD218D74E8617B9A2DE* ____archiveStream;
	ZipArchiveEntry_tEFD75A0570102F8A3DF70A038302146B46071DD4* ____archiveStreamOwner;
	BinaryReader_t9A6D85F0FE9AE4EBB5E8D66997DFD1D84939E158* ____archiveReader;
	int32_t ____mode;
	List_1_tA389B1109F43128C89C6358C6B56C819460CF5B3* ____entries;
	ReadOnlyCollection_1_t15A54E961DBC027444DA89894B8AD689A38CE9AC* ____entriesCollection;
	Dictionary_2_tA1C10CF9D35962FF0289095A43DEE774B7F13C47* ____entriesDictionary;
	bool ____readEntries;
	bool ____leaveOpen;
	int64_t ____centralDirectoryStart;
	bool ____isDisposed;
	uint32_t ____numberOfThisDisk;
	int64_t ____expectedNumberOfEntries;
	Stream_tF844051B786E8F7F4244DBD218D74E8617B9A2DE* ____backingStream;
	ByteU5BU5D_tA6237BF417AE52AD70CFB4EF24A7A82613DF9031* ____archiveComment;
	Encoding_t65CDEF28CF20A7B8C92E85A4E808920C2465F095* ____entryNameEncoding;
};
struct FileStatus_tCB96EDE0D0F945F685B9BBED6DBF0731207458C2 
{
	int32_t ___Flags;
	int32_t ___Mode;
	uint32_t ___Uid;
	uint32_t ___Gid;
	int64_t ___Size;
	int64_t ___ATime;
	int64_t ___ATimeNsec;
	int64_t ___MTime;
	int64_t ___MTimeNsec;
	int64_t ___CTime;
	int64_t ___CTimeNsec;
	int64_t ___BirthTime;
	int64_t ___BirthTimeNsec;
	int64_t ___Dev;
	int64_t ___Ino;
	uint32_t ___UserFlags;
};
struct ArgumentException_tAD90411542A20A9C72D5CDA3A84181D8B947A263  : public SystemException_tCC48D868298F4C0705279823E34B00F4FBDB7295
{
	String_t* ____paramName;
};
struct FileStatus_tABB5F252F1E597EC95E9041035DC424EF66712A5 
{
	FileStatus_tCB96EDE0D0F945F685B9BBED6DBF0731207458C2 ____fileStatus;
	int32_t ____fileStatusInitialized;
	bool ___U3CInitiallyDirectoryU3Ek__BackingField;
	bool ____isDirectory;
	bool ____exists;
};
struct FileStatus_tABB5F252F1E597EC95E9041035DC424EF66712A5_marshaled_pinvoke
{
	FileStatus_tCB96EDE0D0F945F685B9BBED6DBF0731207458C2 ____fileStatus;
	int32_t ____fileStatusInitialized;
	int32_t ___U3CInitiallyDirectoryU3Ek__BackingField;
	int32_t ____isDirectory;
	int32_t ____exists;
};
struct FileStatus_tABB5F252F1E597EC95E9041035DC424EF66712A5_marshaled_com
{
	FileStatus_tCB96EDE0D0F945F685B9BBED6DBF0731207458C2 ____fileStatus;
	int32_t ____fileStatusInitialized;
	int32_t ___U3CInitiallyDirectoryU3Ek__BackingField;
	int32_t ____isDirectory;
	int32_t ____exists;
};
struct ZipArchiveEntry_tEFD75A0570102F8A3DF70A038302146B46071DD4  : public RuntimeObject
{
	ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41* ____archive;
	bool ____originallyInArchive;
	int32_t ____diskNumberStart;
	uint8_t ____versionMadeByPlatform;
	uint16_t ____versionMadeBySpecification;
	uint16_t ____versionToExtract;
	uint16_t ____generalPurposeBitFlag;
	uint16_t ____storedCompressionMethod;
	DateTimeOffset_t4EE701FE2F386D6F932FAC9B11E4B74A5B30F0A4 ____lastModified;
	int64_t ____compressedSize;
	int64_t ____uncompressedSize;
	int64_t ____offsetOfLocalHeader;
	Nullable_1_t365991B3904FDA7642A788423B28692FDC7CDB17 ____storedOffsetOfCompressedData;
	uint32_t ____crc32;
	ByteU5BU5DU5BU5D_t19A0C6D66F22DF673E9CDB37DEF566FE0EC947FA* ____compressedBytes;
	MemoryStream_tAAED1B42172E3390584E4194308AB878E786AAC2* ____storedUncompressedData;
	bool ____currentlyOpenForWrite;
	bool ____everOpenedForWrite;
	Stream_tF844051B786E8F7F4244DBD218D74E8617B9A2DE* ____outstandingWriteStream;
	uint32_t ____externalFileAttr;
	String_t* ____storedEntryName;
	ByteU5BU5D_tA6237BF417AE52AD70CFB4EF24A7A82613DF9031* ____storedEntryNameBytes;
	List_1_t0845A5AAFB6B816C6E2719A0588604CE3A080FDC* ____cdUnknownExtraFields;
	List_1_t0845A5AAFB6B816C6E2719A0588604CE3A080FDC* ____lhUnknownExtraFields;
	ByteU5BU5D_tA6237BF417AE52AD70CFB4EF24A7A82613DF9031* ____fileComment;
	Nullable_1_tAC8899D7718BEF36A8590184EFBCA842A1BC9AB1 ____compressionLevel;
};
struct ArgumentNullException_t327031E412FAB2351B0022DD5DAD47E67E597129  : public ArgumentException_tAD90411542A20A9C72D5CDA3A84181D8B947A263
{
};
struct ArgumentOutOfRangeException_tEA2822DAF62B10EEED00E0E3A341D4BAF78CF85F  : public ArgumentException_tAD90411542A20A9C72D5CDA3A84181D8B947A263
{
	RuntimeObject* ____actualValue;
};
struct FileSystemInfo_tE3063B9229F46B05A5F6D018C8C4CA510104E8E9  : public MarshalByRefObject_t8C2F4C5854177FD60439EB1FCCFC1B3CFAFE8DCE
{
	FileStatus_tABB5F252F1E597EC95E9041035DC424EF66712A5 ____fileStatus;
	String_t* ___FullPath;
	String_t* ___OriginalPath;
	String_t* ____name;
};
struct DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2  : public FileSystemInfo_tE3063B9229F46B05A5F6D018C8C4CA510104E8E9
{
};
struct FileInfo_t62782BBAFA832A78724E4CF2EE96548B8466AB1C  : public FileSystemInfo_tE3063B9229F46B05A5F6D018C8C4CA510104E8E9
{
};
struct ArrayPool_1_t3CE8332C9DFE03FF160AB0CE0FF17DF7792E0E4B_StaticFields
{
	ArrayPool_1_t3CE8332C9DFE03FF160AB0CE0FF17DF7792E0E4B* ___U3CSharedU3Ek__BackingField;
};
struct Encoding_t65CDEF28CF20A7B8C92E85A4E808920C2465F095_StaticFields
{
	Encoding_t65CDEF28CF20A7B8C92E85A4E808920C2465F095* ___defaultEncoding;
	Encoding_t65CDEF28CF20A7B8C92E85A4E808920C2465F095* ___unicodeEncoding;
	Encoding_t65CDEF28CF20A7B8C92E85A4E808920C2465F095* ___bigEndianUnicode;
	Encoding_t65CDEF28CF20A7B8C92E85A4E808920C2465F095* ___utf7Encoding;
	Encoding_t65CDEF28CF20A7B8C92E85A4E808920C2465F095* ___utf8Encoding;
	Encoding_t65CDEF28CF20A7B8C92E85A4E808920C2465F095* ___utf32Encoding;
	Encoding_t65CDEF28CF20A7B8C92E85A4E808920C2465F095* ___asciiEncoding;
	Encoding_t65CDEF28CF20A7B8C92E85A4E808920C2465F095* ___latin1Encoding;
	Dictionary_2_t87EDE08B2E48F793A22DE50D6B3CC2E7EBB2DB54* ___encodings;
	RuntimeObject* ___s_InternalSyncObject;
};
struct Path_t8A38A801D0219E8209C1B1D90D82D4D755D998BC_StaticFields
{
	CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB* ___InvalidPathChars;
	Il2CppChar ___AltDirectorySeparatorChar;
	Il2CppChar ___DirectorySeparatorChar;
	Il2CppChar ___PathSeparator;
	String_t* ___DirectorySeparatorStr;
	Il2CppChar ___VolumeSeparatorChar;
	CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB* ___PathSeparatorChars;
	bool ___dirEqualsVolume;
	CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB* ___trimEndCharsWindows;
	CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB* ___trimEndCharsUnix;
};
struct String_t_StaticFields
{
	String_t* ___Empty;
};
struct Boolean_t09A6377A54BE2F9E6985A8149F19234FD7DDFE22_StaticFields
{
	String_t* ___TrueString;
	String_t* ___FalseString;
};
struct Char_t521A6F19B456D956AF452D926C32709DC03D6B17_StaticFields
{
	ByteU5BU5D_tA6237BF417AE52AD70CFB4EF24A7A82613DF9031* ___s_categoryForLatin1;
};
struct DateTime_t66193957C73913903DDAD89FEDC46139BCA5802D_StaticFields
{
	Int32U5BU5D_t19C97395396A72ECAF310612F0760F165060314C* ___s_daysToMonth365;
	Int32U5BU5D_t19C97395396A72ECAF310612F0760F165060314C* ___s_daysToMonth366;
	DateTime_t66193957C73913903DDAD89FEDC46139BCA5802D ___MinValue;
	DateTime_t66193957C73913903DDAD89FEDC46139BCA5802D ___MaxValue;
	DateTime_t66193957C73913903DDAD89FEDC46139BCA5802D ___UnixEpoch;
};
struct Stream_tF844051B786E8F7F4244DBD218D74E8617B9A2DE_StaticFields
{
	Stream_tF844051B786E8F7F4244DBD218D74E8617B9A2DE* ___Null;
};
struct DateTimeOffset_t4EE701FE2F386D6F932FAC9B11E4B74A5B30F0A4_StaticFields
{
	DateTimeOffset_t4EE701FE2F386D6F932FAC9B11E4B74A5B30F0A4 ___MinValue;
	DateTimeOffset_t4EE701FE2F386D6F932FAC9B11E4B74A5B30F0A4 ___MaxValue;
	DateTimeOffset_t4EE701FE2F386D6F932FAC9B11E4B74A5B30F0A4 ___UnixEpoch;
};
struct FileStream_t07C7222EE10B75F352B89B76E60820160FF10AD8_StaticFields
{
	ByteU5BU5D_tA6237BF417AE52AD70CFB4EF24A7A82613DF9031* ___buf_recycle;
	RuntimeObject* ___buf_recycle_lock;
};
struct ZipArchiveEntry_tEFD75A0570102F8A3DF70A038302146B46071DD4_StaticFields
{
	bool ___s_allowLargeZipArchiveEntriesInUpdateMode;
	uint8_t ___CurrentZipPlatform;
};
#ifdef __clang__
#pragma clang diagnostic pop
#endif
struct CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB  : public RuntimeArray
{
	ALIGN_FIELD (8) Il2CppChar m_Items[1];

	inline Il2CppChar GetAt(il2cpp_array_size_t index) const
	{
		IL2CPP_ARRAY_BOUNDS_CHECK(index, (uint32_t)(this)->max_length);
		return m_Items[index];
	}
	inline Il2CppChar* GetAddressAt(il2cpp_array_size_t index)
	{
		IL2CPP_ARRAY_BOUNDS_CHECK(index, (uint32_t)(this)->max_length);
		return m_Items + index;
	}
	inline void SetAt(il2cpp_array_size_t index, Il2CppChar value)
	{
		IL2CPP_ARRAY_BOUNDS_CHECK(index, (uint32_t)(this)->max_length);
		m_Items[index] = value;
	}
	inline Il2CppChar GetAtUnchecked(il2cpp_array_size_t index) const
	{
		return m_Items[index];
	}
	inline Il2CppChar* GetAddressAtUnchecked(il2cpp_array_size_t index)
	{
		return m_Items + index;
	}
	inline void SetAtUnchecked(il2cpp_array_size_t index, Il2CppChar value)
	{
		m_Items[index] = value;
	}
};


IL2CPP_MANAGED_FORCE_INLINE IL2CPP_METHOD_ATTR ArrayPool_1_t3CE8332C9DFE03FF160AB0CE0FF17DF7792E0E4B* ArrayPool_1_get_Shared_m8EB88B4EDF81135B55DB0F33A749B8087FE4646F_gshared_inline (const RuntimeMethod* method) ;
IL2CPP_MANAGED_FORCE_INLINE IL2CPP_METHOD_ATTR bool Nullable_1_get_HasValue_mB1F55188CDD50D6D725D41F55D2F2540CD15FB20_gshared_inline (Nullable_1_t163D49A1147F217B7BD43BE8ACC8A5CC6B846D14* __this, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR int32_t Nullable_1_get_Value_m0E81D9B6F2BA5FA17AA4366C5179CD09524FCB60_gshared (Nullable_1_t163D49A1147F217B7BD43BE8ACC8A5CC6B846D14* __this, const RuntimeMethod* method) ;

IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void ArgumentOutOfRangeException__ctor_mBC1D5DEEA1BA41DE77228CB27D6BAFEB6DCCBF4A (ArgumentOutOfRangeException_tEA2822DAF62B10EEED00E0E3A341D4BAF78CF85F* __this, String_t* ___0_paramName, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void FileStream__ctor_mB51E4FD96A6B396795C835EFD7B0F0018A3A5029 (FileStream_t07C7222EE10B75F352B89B76E60820160FF10AD8* __this, String_t* ___0_path, int32_t ___1_mode, int32_t ___2_access, int32_t ___3_share, int32_t ___4_bufferSize, bool ___5_useAsync, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void ZipArchive__ctor_m2706DA413E897A83057237178CCC8E51C07230B5 (ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41* __this, Stream_tF844051B786E8F7F4244DBD218D74E8617B9A2DE* ___0_stream, int32_t ___1_mode, bool ___2_leaveOpen, Encoding_t65CDEF28CF20A7B8C92E85A4E808920C2465F095* ___3_entryNameEncoding, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Stream_Dispose_mCDB42F32A17541CCA6D3A5906827A401570B07A8 (Stream_tF844051B786E8F7F4244DBD218D74E8617B9A2DE* __this, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void ZipFile_DoCreateFromDirectory_m3225FCB59A0EDA74A3FED3858155FC2923DBD863 (String_t* ___0_sourceDirectoryName, String_t* ___1_destinationArchiveFileName, Nullable_1_tAC8899D7718BEF36A8590184EFBCA842A1BC9AB1 ___2_compressionLevel, bool ___3_includeBaseDirectory, Encoding_t65CDEF28CF20A7B8C92E85A4E808920C2465F095* ___4_entryNameEncoding, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR String_t* Path_GetFullPath_m9E485D7D38A868A6A5863CBD24677231288EECE2 (String_t* ___0_path, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41* ZipFile_Open_m6F83ACFED32799E052503C5CEAE6DD0D145FCC8D (String_t* ___0_archiveFileName, int32_t ___1_mode, Encoding_t65CDEF28CF20A7B8C92E85A4E808920C2465F095* ___2_entryNameEncoding, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void DirectoryInfo__ctor_m36BC476C58B55083046C0A738157D84E2323E0E9 (DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2* __this, String_t* ___0_path, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2* DirectoryInfo_get_Parent_m2B95E4D3CBA22F8DAA259247ED791F1411D93347 (DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2* __this, const RuntimeMethod* method) ;
inline ArrayPool_1_t3CE8332C9DFE03FF160AB0CE0FF17DF7792E0E4B* ArrayPool_1_get_Shared_m8EB88B4EDF81135B55DB0F33A749B8087FE4646F_inline (const RuntimeMethod* method)
{
	return ((  ArrayPool_1_t3CE8332C9DFE03FF160AB0CE0FF17DF7792E0E4B* (*) (const RuntimeMethod*))ArrayPool_1_get_Shared_m8EB88B4EDF81135B55DB0F33A749B8087FE4646F_gshared_inline)(method);
}
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR RuntimeObject* DirectoryInfo_EnumerateFileSystemInfos_m63DB502DF1805313E60569E012AA90B190BD3149 (DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2* __this, String_t* ___0_searchPattern, int32_t ___1_searchOption, const RuntimeMethod* method) ;
IL2CPP_MANAGED_FORCE_INLINE IL2CPP_METHOD_ATTR int32_t String_get_Length_m42625D67623FA5CC7A44D47425CE86FB946542D2_inline (String_t* __this, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR String_t* ZipFile_EntryFromPath_m86DD579B0B7191BD2C961B8E47BC3832A82FCE7A (String_t* ___0_entry, int32_t ___1_offset, int32_t ___2_length, CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB** ___3_buffer, bool ___4_appendPathSeparator, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR ZipArchiveEntry_tEFD75A0570102F8A3DF70A038302146B46071DD4* ZipFileExtensions_DoCreateEntryFromFile_m0B0768102927FBBB004A43ECE057BE6680B91F26 (ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41* ___0_destination, String_t* ___1_sourceFileName, String_t* ___2_entryName, Nullable_1_tAC8899D7718BEF36A8590184EFBCA842A1BC9AB1 ___3_compressionLevel, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR bool ZipFile_IsDirEmpty_m047A2732228B0C7A9CCEC311958381DCB264635C (DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2* ___0_possiblyEmptyDir, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR ZipArchiveEntry_tEFD75A0570102F8A3DF70A038302146B46071DD4* ZipArchive_CreateEntry_m52C487BC25504F8951CE8927F64778DC417CE88E (ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41* __this, String_t* ___0_entryName, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Il2CppChar String_get_Chars_mC49DF0CD2D3BE7BE97B3AD9C995BE3094F8E36D3 (String_t* __this, int32_t ___0_index, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR String_t* Char_ToString_m2A308731F9577C06AF3C0901234E2EAC8327410C (Il2CppChar* __this, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void ZipFile_EnsureCapacity_m61A3D212DC6CBACFE57140BF095A849607493604 (CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB** ___0_buffer, int32_t ___1_min, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void String_CopyTo_m6E1DE99F2A6481B3B9839C8A026C74887C10A1DC (String_t* __this, int32_t ___0_sourceIndex, CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB* ___1_destination, int32_t ___2_destinationIndex, int32_t ___3_count, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR String_t* String_CreateString_mB7B3AC2AF28010538650051A9000369B1CD6BAB6 (String_t* __this, CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB* ___0_val, int32_t ___1_startIndex, int32_t ___2_length, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR RuntimeObject* Directory_EnumerateFileSystemEntries_mFC14748938E7979CA5472FB025BABE5448E9E216 (String_t* ___0_path, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void ArgumentNullException__ctor_m444AE141157E333844FC1A9500224C2F9FD24F4B (ArgumentNullException_t327031E412FAB2351B0022DD5DAD47E67E597129* __this, String_t* ___0_paramName, const RuntimeMethod* method) ;
inline bool Nullable_1_get_HasValue_mEBB6F9CB853B438D075BB555958691054B188001_inline (Nullable_1_tAC8899D7718BEF36A8590184EFBCA842A1BC9AB1* __this, const RuntimeMethod* method)
{
	return ((  bool (*) (Nullable_1_tAC8899D7718BEF36A8590184EFBCA842A1BC9AB1*, const RuntimeMethod*))Nullable_1_get_HasValue_mB1F55188CDD50D6D725D41F55D2F2540CD15FB20_gshared_inline)(__this, method);
}
inline int32_t Nullable_1_get_Value_mE771FFC5C0CA05BC9996418326C1D36E8A33DB2A (Nullable_1_tAC8899D7718BEF36A8590184EFBCA842A1BC9AB1* __this, const RuntimeMethod* method)
{
	return ((  int32_t (*) (Nullable_1_tAC8899D7718BEF36A8590184EFBCA842A1BC9AB1*, const RuntimeMethod*))Nullable_1_get_Value_m0E81D9B6F2BA5FA17AA4366C5179CD09524FCB60_gshared)(__this, method);
}
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR ZipArchiveEntry_tEFD75A0570102F8A3DF70A038302146B46071DD4* ZipArchive_CreateEntry_m52B44886A7D190AA27F6CA6C56BF5BBA39AE16D3 (ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41* __this, String_t* ___0_entryName, int32_t ___1_compressionLevel, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR DateTime_t66193957C73913903DDAD89FEDC46139BCA5802D File_GetLastWriteTime_m5DD0EAF55C3F704DDB7AC9919504C6FCB6DD6621 (String_t* ___0_path, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR int32_t DateTime_get_Year_m00A88C4CEE07B7906F5F7F75C254B769808F5138 (DateTime_t66193957C73913903DDAD89FEDC46139BCA5802D* __this, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void DateTime__ctor_m1F66A4327FE6B127F0F0E83A70CED25DB0DFFB00 (DateTime_t66193957C73913903DDAD89FEDC46139BCA5802D* __this, int32_t ___0_year, int32_t ___1_month, int32_t ___2_day, int32_t ___3_hour, int32_t ___4_minute, int32_t ___5_second, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR DateTimeOffset_t4EE701FE2F386D6F932FAC9B11E4B74A5B30F0A4 DateTimeOffset_op_Implicit_m7BFCB56BB3714FA7E58AA0ECEE92B8455A0CEDA5 (DateTime_t66193957C73913903DDAD89FEDC46139BCA5802D ___0_dateTime, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void ZipArchiveEntry_set_LastWriteTime_mB37B15E966275E236647AC8F23EC9D03B7C124A7 (ZipArchiveEntry_tEFD75A0570102F8A3DF70A038302146B46071DD4* __this, DateTimeOffset_t4EE701FE2F386D6F932FAC9B11E4B74A5B30F0A4 ___0_value, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Stream_tF844051B786E8F7F4244DBD218D74E8617B9A2DE* ZipArchiveEntry_Open_m1D0EFB9AD33BA96AAF0C624EADA3E58CD6CC67FF (ZipArchiveEntry_tEFD75A0570102F8A3DF70A038302146B46071DD4* __this, const RuntimeMethod* method) ;
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Stream_CopyTo_m61DC54FF3708C2B8AB5C5D63D300AA57ADA01999 (Stream_tF844051B786E8F7F4244DBD218D74E8617B9A2DE* __this, Stream_tF844051B786E8F7F4244DBD218D74E8617B9A2DE* ___0_destination, const RuntimeMethod* method) ;
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// Method Definition Index: 89131
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41* ZipFile_Open_m6F83ACFED32799E052503C5CEAE6DD0D145FCC8D (String_t* ___0_archiveFileName, int32_t ___1_mode, Encoding_t65CDEF28CF20A7B8C92E85A4E808920C2465F095* ___2_entryNameEncoding, const RuntimeMethod* method) 
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_runtime_metadata((uintptr_t*)&FileStream_t07C7222EE10B75F352B89B76E60820160FF10AD8_il2cpp_TypeInfo_var);
		il2cpp_codegen_initialize_runtime_metadata((uintptr_t*)&ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41_il2cpp_TypeInfo_var);
		s_Il2CppMethodInitialized = true;
	}
	int32_t V_0 = 0;
	int32_t V_1 = 0;
	int32_t V_2 = 0;
	FileStream_t07C7222EE10B75F352B89B76E60820160FF10AD8* V_3 = NULL;
	ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41* V_4 = NULL;
	il2cpp::utils::ExceptionSupportStack<RuntimeObject*, 1> __active_exceptions;
	{
		int32_t L_0 = ___1_mode;
		switch (L_0)
		{
			case 0:
			{
				goto IL_0014;
			}
			case 1:
			{
				goto IL_001c;
			}
			case 2:
			{
				goto IL_0024;
			}
		}
	}
	{
		goto IL_002c;
	}

IL_0014:
	{
		V_0 = 3;
		V_1 = 1;
		V_2 = 1;
		goto IL_0037;
	}

IL_001c:
	{
		V_0 = 1;
		V_1 = 2;
		V_2 = 0;
		goto IL_0037;
	}

IL_0024:
	{
		V_0 = 4;
		V_1 = 3;
		V_2 = 0;
		goto IL_0037;
	}

IL_002c:
	{
		ArgumentOutOfRangeException_tEA2822DAF62B10EEED00E0E3A341D4BAF78CF85F* L_1 = (ArgumentOutOfRangeException_tEA2822DAF62B10EEED00E0E3A341D4BAF78CF85F*)il2cpp_codegen_object_new(((RuntimeClass*)il2cpp_codegen_initialize_runtime_metadata_inline((uintptr_t*)&ArgumentOutOfRangeException_tEA2822DAF62B10EEED00E0E3A341D4BAF78CF85F_il2cpp_TypeInfo_var)));
		ArgumentOutOfRangeException__ctor_mBC1D5DEEA1BA41DE77228CB27D6BAFEB6DCCBF4A(L_1, ((String_t*)il2cpp_codegen_initialize_runtime_metadata_inline((uintptr_t*)&_stringLiteralAF248E82BE9EBA1ADBF067429FAEE5A5B6E05A74)), NULL);
		IL2CPP_RAISE_MANAGED_EXCEPTION(L_1, ((RuntimeMethod*)il2cpp_codegen_initialize_runtime_metadata_inline((uintptr_t*)&ZipFile_Open_m6F83ACFED32799E052503C5CEAE6DD0D145FCC8D_RuntimeMethod_var)));
	}

IL_0037:
	{
		String_t* L_2 = ___0_archiveFileName;
		int32_t L_3 = V_0;
		int32_t L_4 = V_1;
		int32_t L_5 = V_2;
		FileStream_t07C7222EE10B75F352B89B76E60820160FF10AD8* L_6 = (FileStream_t07C7222EE10B75F352B89B76E60820160FF10AD8*)il2cpp_codegen_object_new(FileStream_t07C7222EE10B75F352B89B76E60820160FF10AD8_il2cpp_TypeInfo_var);
		FileStream__ctor_mB51E4FD96A6B396795C835EFD7B0F0018A3A5029(L_6, L_2, L_3, L_4, L_5, ((int32_t)4096), (bool)0, NULL);
		V_3 = L_6;
	}
	try
	{
		FileStream_t07C7222EE10B75F352B89B76E60820160FF10AD8* L_7 = V_3;
		int32_t L_8 = ___1_mode;
		Encoding_t65CDEF28CF20A7B8C92E85A4E808920C2465F095* L_9 = ___2_entryNameEncoding;
		ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41* L_10 = (ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41*)il2cpp_codegen_object_new(ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41_il2cpp_TypeInfo_var);
		ZipArchive__ctor_m2706DA413E897A83057237178CCC8E51C07230B5(L_10, L_7, L_8, (bool)0, L_9, NULL);
		V_4 = L_10;
		goto IL_005d;
	}
	catch(Il2CppExceptionWrapper& e)
	{
		if(il2cpp_codegen_class_is_assignable_from (il2cpp_defaults.object_class, il2cpp_codegen_object_class(e.ex)))
		{
			IL2CPP_PUSH_ACTIVE_EXCEPTION(e.ex);
			goto CATCH_0054;
		}
		throw e;
	}

CATCH_0054:
	{
		RuntimeObject* L_11 = ((RuntimeObject*)IL2CPP_GET_ACTIVE_EXCEPTION(RuntimeObject*));;
		FileStream_t07C7222EE10B75F352B89B76E60820160FF10AD8* L_12 = V_3;
		NullCheck(L_12);
		Stream_Dispose_mCDB42F32A17541CCA6D3A5906827A401570B07A8(L_12, NULL);
		IL2CPP_RETHROW_MANAGED_EXCEPTION(IL2CPP_POP_ACTIVE_EXCEPTION(Exception_t*));
	}

IL_005d:
	{
		ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41* L_13 = V_4;
		return L_13;
	}
}
// Method Definition Index: 89132
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void ZipFile_CreateFromDirectory_m80565C16FD9FCBE1C421B8A8E3E315EB74B23877 (String_t* ___0_sourceDirectoryName, String_t* ___1_destinationArchiveFileName, const RuntimeMethod* method) 
{
	Nullable_1_tAC8899D7718BEF36A8590184EFBCA842A1BC9AB1 V_0;
	memset((&V_0), 0, sizeof(V_0));
	{
		String_t* L_0 = ___0_sourceDirectoryName;
		String_t* L_1 = ___1_destinationArchiveFileName;
		il2cpp_codegen_initobj((&V_0), sizeof(Nullable_1_tAC8899D7718BEF36A8590184EFBCA842A1BC9AB1));
		Nullable_1_tAC8899D7718BEF36A8590184EFBCA842A1BC9AB1 L_2 = V_0;
		ZipFile_DoCreateFromDirectory_m3225FCB59A0EDA74A3FED3858155FC2923DBD863(L_0, L_1, L_2, (bool)0, (Encoding_t65CDEF28CF20A7B8C92E85A4E808920C2465F095*)NULL, NULL);
		return;
	}
}
// Method Definition Index: 89133
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void ZipFile_DoCreateFromDirectory_m3225FCB59A0EDA74A3FED3858155FC2923DBD863 (String_t* ___0_sourceDirectoryName, String_t* ___1_destinationArchiveFileName, Nullable_1_tAC8899D7718BEF36A8590184EFBCA842A1BC9AB1 ___2_compressionLevel, bool ___3_includeBaseDirectory, Encoding_t65CDEF28CF20A7B8C92E85A4E808920C2465F095* ___4_entryNameEncoding, const RuntimeMethod* method) 
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_runtime_metadata((uintptr_t*)&ArrayPool_1_get_Shared_m8EB88B4EDF81135B55DB0F33A749B8087FE4646F_RuntimeMethod_var);
		il2cpp_codegen_initialize_runtime_metadata((uintptr_t*)&ArrayPool_1_t3CE8332C9DFE03FF160AB0CE0FF17DF7792E0E4B_il2cpp_TypeInfo_var);
		il2cpp_codegen_initialize_runtime_metadata((uintptr_t*)&DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2_il2cpp_TypeInfo_var);
		il2cpp_codegen_initialize_runtime_metadata((uintptr_t*)&FileInfo_t62782BBAFA832A78724E4CF2EE96548B8466AB1C_il2cpp_TypeInfo_var);
		il2cpp_codegen_initialize_runtime_metadata((uintptr_t*)&IDisposable_t030E0496B4E0E4E4F086825007979AF51F7248C5_il2cpp_TypeInfo_var);
		il2cpp_codegen_initialize_runtime_metadata((uintptr_t*)&IEnumerable_1_t8D7AC720F84EFB74460403413F0F6BE54649BAF0_il2cpp_TypeInfo_var);
		il2cpp_codegen_initialize_runtime_metadata((uintptr_t*)&IEnumerator_1_tB2588994D1BF27F8465E01E530B6EC04F04ED369_il2cpp_TypeInfo_var);
		il2cpp_codegen_initialize_runtime_metadata((uintptr_t*)&IEnumerator_t7B609C2FFA6EB5167D9C62A0C32A21DE2F666DAA_il2cpp_TypeInfo_var);
		il2cpp_codegen_initialize_runtime_metadata((uintptr_t*)&Path_t8A38A801D0219E8209C1B1D90D82D4D755D998BC_il2cpp_TypeInfo_var);
		il2cpp_codegen_initialize_runtime_metadata((uintptr_t*)&_stringLiteralE280D065A824A791F8305234D3E093FC9A5A90C7);
		s_Il2CppMethodInitialized = true;
	}
	ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41* V_0 = NULL;
	bool V_1 = false;
	DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2* V_2 = NULL;
	String_t* V_3 = NULL;
	CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB* V_4 = NULL;
	RuntimeObject* V_5 = NULL;
	FileSystemInfo_tE3063B9229F46B05A5F6D018C8C4CA510104E8E9* V_6 = NULL;
	int32_t V_7 = 0;
	String_t* V_8 = NULL;
	DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2* V_9 = NULL;
	String_t* V_10 = NULL;
	{
		String_t* L_0 = ___0_sourceDirectoryName;
		il2cpp_codegen_runtime_class_init_inline(Path_t8A38A801D0219E8209C1B1D90D82D4D755D998BC_il2cpp_TypeInfo_var);
		String_t* L_1;
		L_1 = Path_GetFullPath_m9E485D7D38A868A6A5863CBD24677231288EECE2(L_0, NULL);
		___0_sourceDirectoryName = L_1;
		String_t* L_2 = ___1_destinationArchiveFileName;
		String_t* L_3;
		L_3 = Path_GetFullPath_m9E485D7D38A868A6A5863CBD24677231288EECE2(L_2, NULL);
		___1_destinationArchiveFileName = L_3;
		String_t* L_4 = ___1_destinationArchiveFileName;
		Encoding_t65CDEF28CF20A7B8C92E85A4E808920C2465F095* L_5 = ___4_entryNameEncoding;
		ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41* L_6;
		L_6 = ZipFile_Open_m6F83ACFED32799E052503C5CEAE6DD0D145FCC8D(L_4, 1, L_5, NULL);
		V_0 = L_6;
	}
	{
		auto __finallyBlock = il2cpp::utils::Finally([&]
		{

FINALLY_0147:
			{
				{
					ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41* L_7 = V_0;
					if (!L_7)
					{
						goto IL_0150;
					}
				}
				{
					ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41* L_8 = V_0;
					NullCheck(L_8);
					InterfaceActionInvoker0::Invoke(0, IDisposable_t030E0496B4E0E4E4F086825007979AF51F7248C5_il2cpp_TypeInfo_var, L_8);
				}

IL_0150:
				{
					return;
				}
			}
		});
		try
		{
			{
				V_1 = (bool)1;
				String_t* L_9 = ___0_sourceDirectoryName;
				DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2* L_10 = (DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2*)il2cpp_codegen_object_new(DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2_il2cpp_TypeInfo_var);
				DirectoryInfo__ctor_m36BC476C58B55083046C0A738157D84E2323E0E9(L_10, L_9, NULL);
				V_2 = L_10;
				DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2* L_11 = V_2;
				NullCheck(L_11);
				String_t* L_12;
				L_12 = VirtualFuncInvoker0< String_t* >::Invoke(8, L_11);
				V_3 = L_12;
				bool L_13 = ___3_includeBaseDirectory;
				if (!L_13)
				{
					goto IL_0041_1;
				}
			}
			{
				DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2* L_14 = V_2;
				NullCheck(L_14);
				DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2* L_15;
				L_15 = DirectoryInfo_get_Parent_m2B95E4D3CBA22F8DAA259247ED791F1411D93347(L_14, NULL);
				if (!L_15)
				{
					goto IL_0041_1;
				}
			}
			{
				DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2* L_16 = V_2;
				NullCheck(L_16);
				DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2* L_17;
				L_17 = DirectoryInfo_get_Parent_m2B95E4D3CBA22F8DAA259247ED791F1411D93347(L_16, NULL);
				NullCheck(L_17);
				String_t* L_18;
				L_18 = VirtualFuncInvoker0< String_t* >::Invoke(8, L_17);
				V_3 = L_18;
			}

IL_0041_1:
			{
				il2cpp_codegen_runtime_class_init_inline(ArrayPool_1_t3CE8332C9DFE03FF160AB0CE0FF17DF7792E0E4B_il2cpp_TypeInfo_var);
				ArrayPool_1_t3CE8332C9DFE03FF160AB0CE0FF17DF7792E0E4B* L_19;
				L_19 = ArrayPool_1_get_Shared_m8EB88B4EDF81135B55DB0F33A749B8087FE4646F_inline(ArrayPool_1_get_Shared_m8EB88B4EDF81135B55DB0F33A749B8087FE4646F_RuntimeMethod_var);
				NullCheck(L_19);
				CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB* L_20;
				L_20 = VirtualFuncInvoker1< CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB*, int32_t >::Invoke(4, L_19, ((int32_t)260));
				V_4 = L_20;
			}
			{
				auto __finallyBlock = il2cpp::utils::Finally([&]
				{

FINALLY_0139_1:
					{
						il2cpp_codegen_runtime_class_init_inline(ArrayPool_1_t3CE8332C9DFE03FF160AB0CE0FF17DF7792E0E4B_il2cpp_TypeInfo_var);
						ArrayPool_1_t3CE8332C9DFE03FF160AB0CE0FF17DF7792E0E4B* L_21;
						L_21 = ArrayPool_1_get_Shared_m8EB88B4EDF81135B55DB0F33A749B8087FE4646F_inline(ArrayPool_1_get_Shared_m8EB88B4EDF81135B55DB0F33A749B8087FE4646F_RuntimeMethod_var);
						CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB* L_22 = V_4;
						NullCheck(L_21);
						VirtualActionInvoker2< CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB*, bool >::Invoke(5, L_21, L_22, (bool)0);
						return;
					}
				});
				try
				{
					{
						DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2* L_23 = V_2;
						NullCheck(L_23);
						RuntimeObject* L_24;
						L_24 = DirectoryInfo_EnumerateFileSystemInfos_m63DB502DF1805313E60569E012AA90B190BD3149(L_23, _stringLiteralE280D065A824A791F8305234D3E093FC9A5A90C7, 1, NULL);
						NullCheck(L_24);
						RuntimeObject* L_25;
						L_25 = InterfaceFuncInvoker0< RuntimeObject* >::Invoke(0, IEnumerable_1_t8D7AC720F84EFB74460403413F0F6BE54649BAF0_il2cpp_TypeInfo_var, L_24);
						V_5 = L_25;
					}
					{
						auto __finallyBlock = il2cpp::utils::Finally([&]
						{

FINALLY_0105_2:
							{
								{
									RuntimeObject* L_26 = V_5;
									if (!L_26)
									{
										goto IL_0110_2;
									}
								}
								{
									RuntimeObject* L_27 = V_5;
									NullCheck(L_27);
									InterfaceActionInvoker0::Invoke(0, IDisposable_t030E0496B4E0E4E4F086825007979AF51F7248C5_il2cpp_TypeInfo_var, L_27);
								}

IL_0110_2:
								{
									return;
								}
							}
						});
						try
						{
							{
								goto IL_00f7_3;
							}

IL_006a_3:
							{
								RuntimeObject* L_28 = V_5;
								NullCheck(L_28);
								FileSystemInfo_tE3063B9229F46B05A5F6D018C8C4CA510104E8E9* L_29;
								L_29 = InterfaceFuncInvoker0< FileSystemInfo_tE3063B9229F46B05A5F6D018C8C4CA510104E8E9* >::Invoke(0, IEnumerator_1_tB2588994D1BF27F8465E01E530B6EC04F04ED369_il2cpp_TypeInfo_var, L_28);
								V_6 = L_29;
								V_1 = (bool)0;
								FileSystemInfo_tE3063B9229F46B05A5F6D018C8C4CA510104E8E9* L_30 = V_6;
								NullCheck(L_30);
								String_t* L_31;
								L_31 = VirtualFuncInvoker0< String_t* >::Invoke(8, L_30);
								NullCheck(L_31);
								int32_t L_32;
								L_32 = String_get_Length_m42625D67623FA5CC7A44D47425CE86FB946542D2_inline(L_31, NULL);
								String_t* L_33 = V_3;
								NullCheck(L_33);
								int32_t L_34;
								L_34 = String_get_Length_m42625D67623FA5CC7A44D47425CE86FB946542D2_inline(L_33, NULL);
								V_7 = ((int32_t)il2cpp_codegen_subtract(L_32, L_34));
								FileSystemInfo_tE3063B9229F46B05A5F6D018C8C4CA510104E8E9* L_35 = V_6;
								if (!((FileInfo_t62782BBAFA832A78724E4CF2EE96548B8466AB1C*)IsInstSealed((RuntimeObject*)L_35, FileInfo_t62782BBAFA832A78724E4CF2EE96548B8466AB1C_il2cpp_TypeInfo_var)))
								{
									goto IL_00bf_3;
								}
							}
							{
								FileSystemInfo_tE3063B9229F46B05A5F6D018C8C4CA510104E8E9* L_36 = V_6;
								NullCheck(L_36);
								String_t* L_37;
								L_37 = VirtualFuncInvoker0< String_t* >::Invoke(8, L_36);
								String_t* L_38 = V_3;
								NullCheck(L_38);
								int32_t L_39;
								L_39 = String_get_Length_m42625D67623FA5CC7A44D47425CE86FB946542D2_inline(L_38, NULL);
								int32_t L_40 = V_7;
								String_t* L_41;
								L_41 = ZipFile_EntryFromPath_m86DD579B0B7191BD2C961B8E47BC3832A82FCE7A(L_37, L_39, L_40, (&V_4), (bool)0, NULL);
								V_8 = L_41;
								ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41* L_42 = V_0;
								FileSystemInfo_tE3063B9229F46B05A5F6D018C8C4CA510104E8E9* L_43 = V_6;
								NullCheck(L_43);
								String_t* L_44;
								L_44 = VirtualFuncInvoker0< String_t* >::Invoke(8, L_43);
								String_t* L_45 = V_8;
								Nullable_1_tAC8899D7718BEF36A8590184EFBCA842A1BC9AB1 L_46 = ___2_compressionLevel;
								ZipArchiveEntry_tEFD75A0570102F8A3DF70A038302146B46071DD4* L_47;
								L_47 = ZipFileExtensions_DoCreateEntryFromFile_m0B0768102927FBBB004A43ECE057BE6680B91F26(L_42, L_44, L_45, L_46, NULL);
								goto IL_00f7_3;
							}

IL_00bf_3:
							{
								FileSystemInfo_tE3063B9229F46B05A5F6D018C8C4CA510104E8E9* L_48 = V_6;
								V_9 = ((DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2*)IsInstSealed((RuntimeObject*)L_48, DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2_il2cpp_TypeInfo_var));
								DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2* L_49 = V_9;
								if (!L_49)
								{
									goto IL_00f7_3;
								}
							}
							{
								DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2* L_50 = V_9;
								bool L_51;
								L_51 = ZipFile_IsDirEmpty_m047A2732228B0C7A9CCEC311958381DCB264635C(L_50, NULL);
								if (!L_51)
								{
									goto IL_00f7_3;
								}
							}
							{
								FileSystemInfo_tE3063B9229F46B05A5F6D018C8C4CA510104E8E9* L_52 = V_6;
								NullCheck(L_52);
								String_t* L_53;
								L_53 = VirtualFuncInvoker0< String_t* >::Invoke(8, L_52);
								String_t* L_54 = V_3;
								NullCheck(L_54);
								int32_t L_55;
								L_55 = String_get_Length_m42625D67623FA5CC7A44D47425CE86FB946542D2_inline(L_54, NULL);
								int32_t L_56 = V_7;
								String_t* L_57;
								L_57 = ZipFile_EntryFromPath_m86DD579B0B7191BD2C961B8E47BC3832A82FCE7A(L_53, L_55, L_56, (&V_4), (bool)1, NULL);
								V_10 = L_57;
								ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41* L_58 = V_0;
								String_t* L_59 = V_10;
								NullCheck(L_58);
								ZipArchiveEntry_tEFD75A0570102F8A3DF70A038302146B46071DD4* L_60;
								L_60 = ZipArchive_CreateEntry_m52C487BC25504F8951CE8927F64778DC417CE88E(L_58, L_59, NULL);
							}

IL_00f7_3:
							{
								RuntimeObject* L_61 = V_5;
								NullCheck(L_61);
								bool L_62;
								L_62 = InterfaceFuncInvoker0< bool >::Invoke(0, IEnumerator_t7B609C2FFA6EB5167D9C62A0C32A21DE2F666DAA_il2cpp_TypeInfo_var, L_61);
								if (L_62)
								{
									goto IL_006a_3;
								}
							}
							{
								goto IL_0111_2;
							}
						}
						catch(Il2CppExceptionWrapper& e)
						{
							__finallyBlock.StoreException(e.ex);
						}
					}

IL_0111_2:
					{
						bool L_63 = ___3_includeBaseDirectory;
						bool L_64 = V_1;
						if (!((int32_t)((int32_t)L_63&(int32_t)L_64)))
						{
							goto IL_0137_2;
						}
					}
					{
						ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41* L_65 = V_0;
						DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2* L_66 = V_2;
						NullCheck(L_66);
						String_t* L_67;
						L_67 = VirtualFuncInvoker0< String_t* >::Invoke(9, L_66);
						DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2* L_68 = V_2;
						NullCheck(L_68);
						String_t* L_69;
						L_69 = VirtualFuncInvoker0< String_t* >::Invoke(9, L_68);
						NullCheck(L_69);
						int32_t L_70;
						L_70 = String_get_Length_m42625D67623FA5CC7A44D47425CE86FB946542D2_inline(L_69, NULL);
						String_t* L_71;
						L_71 = ZipFile_EntryFromPath_m86DD579B0B7191BD2C961B8E47BC3832A82FCE7A(L_67, 0, L_70, (&V_4), (bool)1, NULL);
						NullCheck(L_65);
						ZipArchiveEntry_tEFD75A0570102F8A3DF70A038302146B46071DD4* L_72;
						L_72 = ZipArchive_CreateEntry_m52C487BC25504F8951CE8927F64778DC417CE88E(L_65, L_71, NULL);
					}

IL_0137_2:
					{
						goto IL_0151;
					}
				}
				catch(Il2CppExceptionWrapper& e)
				{
					__finallyBlock.StoreException(e.ex);
				}
			}
		}
		catch(Il2CppExceptionWrapper& e)
		{
			__finallyBlock.StoreException(e.ex);
		}
	}

IL_0151:
	{
		return;
	}
}
// Method Definition Index: 89134
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR String_t* ZipFile_EntryFromPath_m86DD579B0B7191BD2C961B8E47BC3832A82FCE7A (String_t* ___0_entry, int32_t ___1_offset, int32_t ___2_length, CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB** ___3_buffer, bool ___4_appendPathSeparator, const RuntimeMethod* method) 
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_runtime_metadata((uintptr_t*)&Path_t8A38A801D0219E8209C1B1D90D82D4D755D998BC_il2cpp_TypeInfo_var);
		s_Il2CppMethodInitialized = true;
	}
	int32_t V_0 = 0;
	Il2CppChar V_1 = 0x0;
	int32_t V_2 = 0;
	Il2CppChar V_3 = 0x0;
	int32_t G_B12_0 = 0;
	{
		goto IL_0028;
	}

IL_0002:
	{
		String_t* L_0 = ___0_entry;
		int32_t L_1 = ___1_offset;
		NullCheck(L_0);
		Il2CppChar L_2;
		L_2 = String_get_Chars_mC49DF0CD2D3BE7BE97B3AD9C995BE3094F8E36D3(L_0, L_1, NULL);
		il2cpp_codegen_runtime_class_init_inline(Path_t8A38A801D0219E8209C1B1D90D82D4D755D998BC_il2cpp_TypeInfo_var);
		Il2CppChar L_3 = ((Path_t8A38A801D0219E8209C1B1D90D82D4D755D998BC_StaticFields*)il2cpp_codegen_static_fields_for(Path_t8A38A801D0219E8209C1B1D90D82D4D755D998BC_il2cpp_TypeInfo_var))->___DirectorySeparatorChar;
		if ((((int32_t)L_2) == ((int32_t)L_3)))
		{
			goto IL_001e;
		}
	}
	{
		String_t* L_4 = ___0_entry;
		int32_t L_5 = ___1_offset;
		NullCheck(L_4);
		Il2CppChar L_6;
		L_6 = String_get_Chars_mC49DF0CD2D3BE7BE97B3AD9C995BE3094F8E36D3(L_4, L_5, NULL);
		il2cpp_codegen_runtime_class_init_inline(Path_t8A38A801D0219E8209C1B1D90D82D4D755D998BC_il2cpp_TypeInfo_var);
		Il2CppChar L_7 = ((Path_t8A38A801D0219E8209C1B1D90D82D4D755D998BC_StaticFields*)il2cpp_codegen_static_fields_for(Path_t8A38A801D0219E8209C1B1D90D82D4D755D998BC_il2cpp_TypeInfo_var))->___AltDirectorySeparatorChar;
		if ((!(((uint32_t)L_6) == ((uint32_t)L_7))))
		{
			goto IL_002c;
		}
	}

IL_001e:
	{
		int32_t L_8 = ___1_offset;
		___1_offset = ((int32_t)il2cpp_codegen_add(L_8, 1));
		int32_t L_9 = ___2_length;
		___2_length = ((int32_t)il2cpp_codegen_subtract(L_9, 1));
	}

IL_0028:
	{
		int32_t L_10 = ___2_length;
		if ((((int32_t)L_10) > ((int32_t)0)))
		{
			goto IL_0002;
		}
	}

IL_002c:
	{
		int32_t L_11 = ___2_length;
		if (L_11)
		{
			goto IL_0044;
		}
	}
	{
		bool L_12 = ___4_appendPathSeparator;
		if (L_12)
		{
			goto IL_0039;
		}
	}
	{
		String_t* L_13 = ((String_t_StaticFields*)il2cpp_codegen_static_fields_for(il2cpp_defaults.string_class))->___Empty;
		return L_13;
	}

IL_0039:
	{
		V_1 = ((int32_t)47);
		il2cpp_codegen_runtime_class_init_inline(il2cpp_defaults.char_class);
		String_t* L_14;
		L_14 = Char_ToString_m2A308731F9577C06AF3C0901234E2EAC8327410C((&V_1), NULL);
		return L_14;
	}

IL_0044:
	{
		bool L_15 = ___4_appendPathSeparator;
		if (L_15)
		{
			goto IL_004b;
		}
	}
	{
		int32_t L_16 = ___2_length;
		G_B12_0 = L_16;
		goto IL_004e;
	}

IL_004b:
	{
		int32_t L_17 = ___2_length;
		G_B12_0 = ((int32_t)il2cpp_codegen_add(L_17, 1));
	}

IL_004e:
	{
		V_0 = G_B12_0;
		CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB** L_18 = ___3_buffer;
		int32_t L_19 = V_0;
		ZipFile_EnsureCapacity_m61A3D212DC6CBACFE57140BF095A849607493604(L_18, L_19, NULL);
		String_t* L_20 = ___0_entry;
		int32_t L_21 = ___1_offset;
		CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB** L_22 = ___3_buffer;
		CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB* L_23 = *((CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB**)L_22);
		int32_t L_24 = ___2_length;
		NullCheck(L_20);
		String_CopyTo_m6E1DE99F2A6481B3B9839C8A026C74887C10A1DC(L_20, L_21, L_23, 0, L_24, NULL);
		V_2 = 0;
		goto IL_0084;
	}

IL_0065:
	{
		CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB** L_25 = ___3_buffer;
		CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB* L_26 = *((CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB**)L_25);
		int32_t L_27 = V_2;
		NullCheck(L_26);
		int32_t L_28 = L_27;
		uint16_t L_29 = (uint16_t)(L_26)->GetAt(static_cast<il2cpp_array_size_t>(L_28));
		V_3 = L_29;
		Il2CppChar L_30 = V_3;
		il2cpp_codegen_runtime_class_init_inline(Path_t8A38A801D0219E8209C1B1D90D82D4D755D998BC_il2cpp_TypeInfo_var);
		Il2CppChar L_31 = ((Path_t8A38A801D0219E8209C1B1D90D82D4D755D998BC_StaticFields*)il2cpp_codegen_static_fields_for(Path_t8A38A801D0219E8209C1B1D90D82D4D755D998BC_il2cpp_TypeInfo_var))->___DirectorySeparatorChar;
		if ((((int32_t)L_30) == ((int32_t)L_31)))
		{
			goto IL_007a;
		}
	}
	{
		Il2CppChar L_32 = V_3;
		il2cpp_codegen_runtime_class_init_inline(Path_t8A38A801D0219E8209C1B1D90D82D4D755D998BC_il2cpp_TypeInfo_var);
		Il2CppChar L_33 = ((Path_t8A38A801D0219E8209C1B1D90D82D4D755D998BC_StaticFields*)il2cpp_codegen_static_fields_for(Path_t8A38A801D0219E8209C1B1D90D82D4D755D998BC_il2cpp_TypeInfo_var))->___AltDirectorySeparatorChar;
		if ((!(((uint32_t)L_32) == ((uint32_t)L_33))))
		{
			goto IL_0080;
		}
	}

IL_007a:
	{
		CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB** L_34 = ___3_buffer;
		CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB* L_35 = *((CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB**)L_34);
		int32_t L_36 = V_2;
		NullCheck(L_35);
		(L_35)->SetAt(static_cast<il2cpp_array_size_t>(L_36), (Il2CppChar)((int32_t)47));
	}

IL_0080:
	{
		int32_t L_37 = V_2;
		V_2 = ((int32_t)il2cpp_codegen_add(L_37, 1));
	}

IL_0084:
	{
		int32_t L_38 = V_2;
		int32_t L_39 = ___2_length;
		if ((((int32_t)L_38) < ((int32_t)L_39)))
		{
			goto IL_0065;
		}
	}
	{
		bool L_40 = ___4_appendPathSeparator;
		if (!L_40)
		{
			goto IL_0092;
		}
	}
	{
		CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB** L_41 = ___3_buffer;
		CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB* L_42 = *((CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB**)L_41);
		int32_t L_43 = ___2_length;
		NullCheck(L_42);
		(L_42)->SetAt(static_cast<il2cpp_array_size_t>(L_43), (Il2CppChar)((int32_t)47));
	}

IL_0092:
	{
		CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB** L_44 = ___3_buffer;
		CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB* L_45 = *((CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB**)L_44);
		int32_t L_46 = V_0;
		String_t* L_47;
		L_47 = String_CreateString_mB7B3AC2AF28010538650051A9000369B1CD6BAB6(NULL, L_45, 0, L_46, NULL);
		return L_47;
	}
}
// Method Definition Index: 89135
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void ZipFile_EnsureCapacity_m61A3D212DC6CBACFE57140BF095A849607493604 (CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB** ___0_buffer, int32_t ___1_min, const RuntimeMethod* method) 
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_runtime_metadata((uintptr_t*)&ArrayPool_1_get_Shared_m8EB88B4EDF81135B55DB0F33A749B8087FE4646F_RuntimeMethod_var);
		il2cpp_codegen_initialize_runtime_metadata((uintptr_t*)&ArrayPool_1_t3CE8332C9DFE03FF160AB0CE0FF17DF7792E0E4B_il2cpp_TypeInfo_var);
		s_Il2CppMethodInitialized = true;
	}
	int32_t V_0 = 0;
	{
		CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB** L_0 = ___0_buffer;
		CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB* L_1 = *((CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB**)L_0);
		NullCheck(L_1);
		int32_t L_2 = ___1_min;
		if ((((int32_t)((int32_t)(((RuntimeArray*)L_1)->max_length))) >= ((int32_t)L_2)))
		{
			goto IL_002e;
		}
	}
	{
		CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB** L_3 = ___0_buffer;
		CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB* L_4 = *((CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB**)L_3);
		NullCheck(L_4);
		V_0 = ((int32_t)il2cpp_codegen_multiply(((int32_t)(((RuntimeArray*)L_4)->max_length)), 2));
		int32_t L_5 = V_0;
		int32_t L_6 = ___1_min;
		if ((((int32_t)L_5) >= ((int32_t)L_6)))
		{
			goto IL_0014;
		}
	}
	{
		int32_t L_7 = ___1_min;
		V_0 = L_7;
	}

IL_0014:
	{
		il2cpp_codegen_runtime_class_init_inline(ArrayPool_1_t3CE8332C9DFE03FF160AB0CE0FF17DF7792E0E4B_il2cpp_TypeInfo_var);
		ArrayPool_1_t3CE8332C9DFE03FF160AB0CE0FF17DF7792E0E4B* L_8;
		L_8 = ArrayPool_1_get_Shared_m8EB88B4EDF81135B55DB0F33A749B8087FE4646F_inline(ArrayPool_1_get_Shared_m8EB88B4EDF81135B55DB0F33A749B8087FE4646F_RuntimeMethod_var);
		CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB** L_9 = ___0_buffer;
		CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB* L_10 = *((CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB**)L_9);
		NullCheck(L_8);
		VirtualActionInvoker2< CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB*, bool >::Invoke(5, L_8, L_10, (bool)0);
		CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB** L_11 = ___0_buffer;
		ArrayPool_1_t3CE8332C9DFE03FF160AB0CE0FF17DF7792E0E4B* L_12;
		L_12 = ArrayPool_1_get_Shared_m8EB88B4EDF81135B55DB0F33A749B8087FE4646F_inline(ArrayPool_1_get_Shared_m8EB88B4EDF81135B55DB0F33A749B8087FE4646F_RuntimeMethod_var);
		int32_t L_13 = V_0;
		NullCheck(L_12);
		CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB* L_14;
		L_14 = VirtualFuncInvoker1< CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB*, int32_t >::Invoke(4, L_12, L_13);
		*((CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB**)L_11) = (CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB*)L_14;
		Il2CppCodeGenWriteBarrier((void**)(CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB**)L_11, (void*)(CharU5BU5D_t799905CF001DD5F13F7DBB310181FC4D8B7D0AAB*)L_14);
	}

IL_002e:
	{
		return;
	}
}
// Method Definition Index: 89136
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR bool ZipFile_IsDirEmpty_m047A2732228B0C7A9CCEC311958381DCB264635C (DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2* ___0_possiblyEmptyDir, const RuntimeMethod* method) 
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_runtime_metadata((uintptr_t*)&IDisposable_t030E0496B4E0E4E4F086825007979AF51F7248C5_il2cpp_TypeInfo_var);
		il2cpp_codegen_initialize_runtime_metadata((uintptr_t*)&IEnumerable_1_t349E66EC5F09B881A8E52EE40A1AB9EC60E08E44_il2cpp_TypeInfo_var);
		il2cpp_codegen_initialize_runtime_metadata((uintptr_t*)&IEnumerator_t7B609C2FFA6EB5167D9C62A0C32A21DE2F666DAA_il2cpp_TypeInfo_var);
		s_Il2CppMethodInitialized = true;
	}
	RuntimeObject* V_0 = NULL;
	bool V_1 = false;
	{
		DirectoryInfo_tEAEEC018EB49B4A71907FFEAFE935FAA8F9C1FE2* L_0 = ___0_possiblyEmptyDir;
		NullCheck(L_0);
		String_t* L_1;
		L_1 = VirtualFuncInvoker0< String_t* >::Invoke(8, L_0);
		RuntimeObject* L_2;
		L_2 = Directory_EnumerateFileSystemEntries_mFC14748938E7979CA5472FB025BABE5448E9E216(L_1, NULL);
		NullCheck(L_2);
		RuntimeObject* L_3;
		L_3 = InterfaceFuncInvoker0< RuntimeObject* >::Invoke(0, IEnumerable_1_t349E66EC5F09B881A8E52EE40A1AB9EC60E08E44_il2cpp_TypeInfo_var, L_2);
		V_0 = L_3;
	}
	{
		auto __finallyBlock = il2cpp::utils::Finally([&]
		{

FINALLY_001d:
			{
				{
					RuntimeObject* L_4 = V_0;
					if (!L_4)
					{
						goto IL_0026;
					}
				}
				{
					RuntimeObject* L_5 = V_0;
					NullCheck(L_5);
					InterfaceActionInvoker0::Invoke(0, IDisposable_t030E0496B4E0E4E4F086825007979AF51F7248C5_il2cpp_TypeInfo_var, L_5);
				}

IL_0026:
				{
					return;
				}
			}
		});
		try
		{
			RuntimeObject* L_6 = V_0;
			NullCheck(L_6);
			bool L_7;
			L_7 = InterfaceFuncInvoker0< bool >::Invoke(0, IEnumerator_t7B609C2FFA6EB5167D9C62A0C32A21DE2F666DAA_il2cpp_TypeInfo_var, L_6);
			V_1 = (bool)((((int32_t)L_7) == ((int32_t)0))? 1 : 0);
			goto IL_0027;
		}
		catch(Il2CppExceptionWrapper& e)
		{
			__finallyBlock.StoreException(e.ex);
		}
	}

IL_0027:
	{
		bool L_8 = V_1;
		return L_8;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// Method Definition Index: 89137
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR ZipArchiveEntry_tEFD75A0570102F8A3DF70A038302146B46071DD4* ZipFileExtensions_DoCreateEntryFromFile_m0B0768102927FBBB004A43ECE057BE6680B91F26 (ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41* ___0_destination, String_t* ___1_sourceFileName, String_t* ___2_entryName, Nullable_1_tAC8899D7718BEF36A8590184EFBCA842A1BC9AB1 ___3_compressionLevel, const RuntimeMethod* method) 
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_runtime_metadata((uintptr_t*)&DateTimeOffset_t4EE701FE2F386D6F932FAC9B11E4B74A5B30F0A4_il2cpp_TypeInfo_var);
		il2cpp_codegen_initialize_runtime_metadata((uintptr_t*)&DateTime_t66193957C73913903DDAD89FEDC46139BCA5802D_il2cpp_TypeInfo_var);
		il2cpp_codegen_initialize_runtime_metadata((uintptr_t*)&FileStream_t07C7222EE10B75F352B89B76E60820160FF10AD8_il2cpp_TypeInfo_var);
		il2cpp_codegen_initialize_runtime_metadata((uintptr_t*)&IDisposable_t030E0496B4E0E4E4F086825007979AF51F7248C5_il2cpp_TypeInfo_var);
		il2cpp_codegen_initialize_runtime_metadata((uintptr_t*)&Nullable_1_get_HasValue_mEBB6F9CB853B438D075BB555958691054B188001_RuntimeMethod_var);
		il2cpp_codegen_initialize_runtime_metadata((uintptr_t*)&Nullable_1_get_Value_mE771FFC5C0CA05BC9996418326C1D36E8A33DB2A_RuntimeMethod_var);
		s_Il2CppMethodInitialized = true;
	}
	Stream_tF844051B786E8F7F4244DBD218D74E8617B9A2DE* V_0 = NULL;
	ZipArchiveEntry_tEFD75A0570102F8A3DF70A038302146B46071DD4* V_1 = NULL;
	DateTime_t66193957C73913903DDAD89FEDC46139BCA5802D V_2;
	memset((&V_2), 0, sizeof(V_2));
	Stream_tF844051B786E8F7F4244DBD218D74E8617B9A2DE* V_3 = NULL;
	ZipArchiveEntry_tEFD75A0570102F8A3DF70A038302146B46071DD4* V_4 = NULL;
	ZipArchiveEntry_tEFD75A0570102F8A3DF70A038302146B46071DD4* G_B10_0 = NULL;
	{
		ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41* L_0 = ___0_destination;
		if (L_0)
		{
			goto IL_000e;
		}
	}
	{
		ArgumentNullException_t327031E412FAB2351B0022DD5DAD47E67E597129* L_1 = (ArgumentNullException_t327031E412FAB2351B0022DD5DAD47E67E597129*)il2cpp_codegen_object_new(((RuntimeClass*)il2cpp_codegen_initialize_runtime_metadata_inline((uintptr_t*)&ArgumentNullException_t327031E412FAB2351B0022DD5DAD47E67E597129_il2cpp_TypeInfo_var)));
		ArgumentNullException__ctor_m444AE141157E333844FC1A9500224C2F9FD24F4B(L_1, ((String_t*)il2cpp_codegen_initialize_runtime_metadata_inline((uintptr_t*)&_stringLiteralD89ADD2DB1FBF30630EEA02FAAF144060CA0E908)), NULL);
		IL2CPP_RAISE_MANAGED_EXCEPTION(L_1, ((RuntimeMethod*)il2cpp_codegen_initialize_runtime_metadata_inline((uintptr_t*)&ZipFileExtensions_DoCreateEntryFromFile_m0B0768102927FBBB004A43ECE057BE6680B91F26_RuntimeMethod_var)));
	}

IL_000e:
	{
		String_t* L_2 = ___1_sourceFileName;
		if (L_2)
		{
			goto IL_001c;
		}
	}
	{
		ArgumentNullException_t327031E412FAB2351B0022DD5DAD47E67E597129* L_3 = (ArgumentNullException_t327031E412FAB2351B0022DD5DAD47E67E597129*)il2cpp_codegen_object_new(((RuntimeClass*)il2cpp_codegen_initialize_runtime_metadata_inline((uintptr_t*)&ArgumentNullException_t327031E412FAB2351B0022DD5DAD47E67E597129_il2cpp_TypeInfo_var)));
		ArgumentNullException__ctor_m444AE141157E333844FC1A9500224C2F9FD24F4B(L_3, ((String_t*)il2cpp_codegen_initialize_runtime_metadata_inline((uintptr_t*)&_stringLiteral56F96CA2C7CD86A940882DB30231478A10E0B61F)), NULL);
		IL2CPP_RAISE_MANAGED_EXCEPTION(L_3, ((RuntimeMethod*)il2cpp_codegen_initialize_runtime_metadata_inline((uintptr_t*)&ZipFileExtensions_DoCreateEntryFromFile_m0B0768102927FBBB004A43ECE057BE6680B91F26_RuntimeMethod_var)));
	}

IL_001c:
	{
		String_t* L_4 = ___2_entryName;
		if (L_4)
		{
			goto IL_002a;
		}
	}
	{
		ArgumentNullException_t327031E412FAB2351B0022DD5DAD47E67E597129* L_5 = (ArgumentNullException_t327031E412FAB2351B0022DD5DAD47E67E597129*)il2cpp_codegen_object_new(((RuntimeClass*)il2cpp_codegen_initialize_runtime_metadata_inline((uintptr_t*)&ArgumentNullException_t327031E412FAB2351B0022DD5DAD47E67E597129_il2cpp_TypeInfo_var)));
		ArgumentNullException__ctor_m444AE141157E333844FC1A9500224C2F9FD24F4B(L_5, ((String_t*)il2cpp_codegen_initialize_runtime_metadata_inline((uintptr_t*)&_stringLiteralEC39AAB8B28BCEDAFA6F3285CC603CE852769989)), NULL);
		IL2CPP_RAISE_MANAGED_EXCEPTION(L_5, ((RuntimeMethod*)il2cpp_codegen_initialize_runtime_metadata_inline((uintptr_t*)&ZipFileExtensions_DoCreateEntryFromFile_m0B0768102927FBBB004A43ECE057BE6680B91F26_RuntimeMethod_var)));
	}

IL_002a:
	{
		String_t* L_6 = ___1_sourceFileName;
		FileStream_t07C7222EE10B75F352B89B76E60820160FF10AD8* L_7 = (FileStream_t07C7222EE10B75F352B89B76E60820160FF10AD8*)il2cpp_codegen_object_new(FileStream_t07C7222EE10B75F352B89B76E60820160FF10AD8_il2cpp_TypeInfo_var);
		FileStream__ctor_mB51E4FD96A6B396795C835EFD7B0F0018A3A5029(L_7, L_6, 3, 1, 1, ((int32_t)4096), (bool)0, NULL);
		V_0 = L_7;
	}
	{
		auto __finallyBlock = il2cpp::utils::Finally([&]
		{

FINALLY_00ba:
			{
				{
					Stream_tF844051B786E8F7F4244DBD218D74E8617B9A2DE* L_8 = V_0;
					if (!L_8)
					{
						goto IL_00c3;
					}
				}
				{
					Stream_tF844051B786E8F7F4244DBD218D74E8617B9A2DE* L_9 = V_0;
					NullCheck(L_9);
					InterfaceActionInvoker0::Invoke(0, IDisposable_t030E0496B4E0E4E4F086825007979AF51F7248C5_il2cpp_TypeInfo_var, L_9);
				}

IL_00c3:
				{
					return;
				}
			}
		});
		try
		{
			{
				bool L_10;
				L_10 = Nullable_1_get_HasValue_mEBB6F9CB853B438D075BB555958691054B188001_inline((&___3_compressionLevel), Nullable_1_get_HasValue_mEBB6F9CB853B438D075BB555958691054B188001_RuntimeMethod_var);
				if (L_10)
				{
					goto IL_004c_1;
				}
			}
			{
				ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41* L_11 = ___0_destination;
				String_t* L_12 = ___2_entryName;
				NullCheck(L_11);
				ZipArchiveEntry_tEFD75A0570102F8A3DF70A038302146B46071DD4* L_13;
				L_13 = ZipArchive_CreateEntry_m52C487BC25504F8951CE8927F64778DC417CE88E(L_11, L_12, NULL);
				G_B10_0 = L_13;
				goto IL_005a_1;
			}

IL_004c_1:
			{
				ZipArchive_t6469B8DB5F18FB4C7E24F625D0E53EA635D31C41* L_14 = ___0_destination;
				String_t* L_15 = ___2_entryName;
				int32_t L_16;
				L_16 = Nullable_1_get_Value_mE771FFC5C0CA05BC9996418326C1D36E8A33DB2A((&___3_compressionLevel), Nullable_1_get_Value_mE771FFC5C0CA05BC9996418326C1D36E8A33DB2A_RuntimeMethod_var);
				NullCheck(L_14);
				ZipArchiveEntry_tEFD75A0570102F8A3DF70A038302146B46071DD4* L_17;
				L_17 = ZipArchive_CreateEntry_m52B44886A7D190AA27F6CA6C56BF5BBA39AE16D3(L_14, L_15, L_16, NULL);
				G_B10_0 = L_17;
			}

IL_005a_1:
			{
				V_1 = G_B10_0;
				String_t* L_18 = ___1_sourceFileName;
				DateTime_t66193957C73913903DDAD89FEDC46139BCA5802D L_19;
				L_19 = File_GetLastWriteTime_m5DD0EAF55C3F704DDB7AC9919504C6FCB6DD6621(L_18, NULL);
				V_2 = L_19;
				il2cpp_codegen_runtime_class_init_inline(DateTime_t66193957C73913903DDAD89FEDC46139BCA5802D_il2cpp_TypeInfo_var);
				int32_t L_20;
				L_20 = DateTime_get_Year_m00A88C4CEE07B7906F5F7F75C254B769808F5138((&V_2), NULL);
				if ((((int32_t)L_20) < ((int32_t)((int32_t)1980))))
				{
					goto IL_007e_1;
				}
			}
			{
				il2cpp_codegen_runtime_class_init_inline(DateTime_t66193957C73913903DDAD89FEDC46139BCA5802D_il2cpp_TypeInfo_var);
				int32_t L_21;
				L_21 = DateTime_get_Year_m00A88C4CEE07B7906F5F7F75C254B769808F5138((&V_2), NULL);
				if ((((int32_t)L_21) <= ((int32_t)((int32_t)2107))))
				{
					goto IL_008f_1;
				}
			}

IL_007e_1:
			{
				il2cpp_codegen_runtime_class_init_inline(DateTime_t66193957C73913903DDAD89FEDC46139BCA5802D_il2cpp_TypeInfo_var);
				DateTime__ctor_m1F66A4327FE6B127F0F0E83A70CED25DB0DFFB00((&V_2), ((int32_t)1980), 1, 1, 0, 0, 0, NULL);
			}

IL_008f_1:
			{
				ZipArchiveEntry_tEFD75A0570102F8A3DF70A038302146B46071DD4* L_22 = V_1;
				DateTime_t66193957C73913903DDAD89FEDC46139BCA5802D L_23 = V_2;
				il2cpp_codegen_runtime_class_init_inline(DateTimeOffset_t4EE701FE2F386D6F932FAC9B11E4B74A5B30F0A4_il2cpp_TypeInfo_var);
				DateTimeOffset_t4EE701FE2F386D6F932FAC9B11E4B74A5B30F0A4 L_24;
				L_24 = DateTimeOffset_op_Implicit_m7BFCB56BB3714FA7E58AA0ECEE92B8455A0CEDA5(L_23, NULL);
				NullCheck(L_22);
				ZipArchiveEntry_set_LastWriteTime_mB37B15E966275E236647AC8F23EC9D03B7C124A7(L_22, L_24, NULL);
				ZipArchiveEntry_tEFD75A0570102F8A3DF70A038302146B46071DD4* L_25 = V_1;
				NullCheck(L_25);
				Stream_tF844051B786E8F7F4244DBD218D74E8617B9A2DE* L_26;
				L_26 = ZipArchiveEntry_Open_m1D0EFB9AD33BA96AAF0C624EADA3E58CD6CC67FF(L_25, NULL);
				V_3 = L_26;
			}
			{
				auto __finallyBlock = il2cpp::utils::Finally([&]
				{

FINALLY_00ab_1:
					{
						{
							Stream_tF844051B786E8F7F4244DBD218D74E8617B9A2DE* L_27 = V_3;
							if (!L_27)
							{
								goto IL_00b4_1;
							}
						}
						{
							Stream_tF844051B786E8F7F4244DBD218D74E8617B9A2DE* L_28 = V_3;
							NullCheck(L_28);
							InterfaceActionInvoker0::Invoke(0, IDisposable_t030E0496B4E0E4E4F086825007979AF51F7248C5_il2cpp_TypeInfo_var, L_28);
						}

IL_00b4_1:
						{
							return;
						}
					}
				});
				try
				{
					Stream_tF844051B786E8F7F4244DBD218D74E8617B9A2DE* L_29 = V_0;
					Stream_tF844051B786E8F7F4244DBD218D74E8617B9A2DE* L_30 = V_3;
					NullCheck(L_29);
					Stream_CopyTo_m61DC54FF3708C2B8AB5C5D63D300AA57ADA01999(L_29, L_30, NULL);
					goto IL_00b5_1;
				}
				catch(Il2CppExceptionWrapper& e)
				{
					__finallyBlock.StoreException(e.ex);
				}
			}

IL_00b5_1:
			{
				ZipArchiveEntry_tEFD75A0570102F8A3DF70A038302146B46071DD4* L_31 = V_1;
				V_4 = L_31;
				goto IL_00c4;
			}
		}
		catch(Il2CppExceptionWrapper& e)
		{
			__finallyBlock.StoreException(e.ex);
		}
	}

IL_00c4:
	{
		ZipArchiveEntry_tEFD75A0570102F8A3DF70A038302146B46071DD4* L_32 = V_4;
		return L_32;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
// Method Definition Index: 446
IL2CPP_MANAGED_FORCE_INLINE IL2CPP_METHOD_ATTR int32_t String_get_Length_m42625D67623FA5CC7A44D47425CE86FB946542D2_inline (String_t* __this, const RuntimeMethod* method) 
{
	{
		int32_t L_0 = __this->____stringLength;
		return L_0;
	}
}
// Method Definition Index: 9851
IL2CPP_MANAGED_FORCE_INLINE IL2CPP_METHOD_ATTR ArrayPool_1_t3CE8332C9DFE03FF160AB0CE0FF17DF7792E0E4B* ArrayPool_1_get_Shared_m8EB88B4EDF81135B55DB0F33A749B8087FE4646F_gshared_inline (const RuntimeMethod* method) 
{
	{
		il2cpp_codegen_runtime_class_init_inline(il2cpp_rgctx_data(InitializedTypeInfo(method->klass)->rgctx_data, 1));
		ArrayPool_1_t3CE8332C9DFE03FF160AB0CE0FF17DF7792E0E4B* L_0 = ((ArrayPool_1_t3CE8332C9DFE03FF160AB0CE0FF17DF7792E0E4B_StaticFields*)il2cpp_codegen_static_fields_for(il2cpp_rgctx_data(InitializedTypeInfo(method->klass)->rgctx_data, 1)))->___U3CSharedU3Ek__BackingField;
		return L_0;
	}
}
// Method Definition Index: 1775
IL2CPP_MANAGED_FORCE_INLINE IL2CPP_METHOD_ATTR bool Nullable_1_get_HasValue_mB1F55188CDD50D6D725D41F55D2F2540CD15FB20_gshared_inline (Nullable_1_t163D49A1147F217B7BD43BE8ACC8A5CC6B846D14* __this, const RuntimeMethod* method) 
{
	{
		bool L_0 = __this->___hasValue;
		return L_0;
	}
}
