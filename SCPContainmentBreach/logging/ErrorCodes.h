#ifndef HF_ERRORCODES
#define HF_ERRORCODES
enum ErrorCodes {
	EC_UNKNOWN = -1,
	EC_ZERO = 0,
	EC_NOERROR = 1,
	EC_ERRORGENERAL = 2,
	EC_CRASHERROR = 3,
	ECGLOOP_EXITED = 1000,
	ECGLOOP_EXITED_UNEXPECTED = 1001,
	ECGLOOP_FORCEEXITED = 1002,
	ECGLOOP_UPDATING_ERROR = 1110,
	ECGLOOP_RENDERING_ERROR = 1111,

	ECWINDOW_EXIT = 1500
};
#endif