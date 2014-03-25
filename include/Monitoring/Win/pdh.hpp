1	/**
2	 * This file has no copyright assigned and is placed in the Public Domain.
3	 * This file is part of the mingw-w64 runtime package.
4	 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
5	 */
6	#ifndef _PDH_H_
7	#define _PDH_H_
8
9	#include <_mingw_unicode.h>
10	#include <windows.h>
11	#include <winperf.h>
12
13	#ifdef __cplusplus
14	extern "C" {
15	#endif
16
17	  typedef LONG PDH_STATUS;
18
19	#define PDH_FUNCTION PDH_STATUS WINAPI
20
21	#define PDH_CVERSION_WIN40 ((DWORD)(0x0400))
22	#define PDH_CVERSION_WIN50 ((DWORD)(0x0500))
23
24	#define PDH_VERSION ((DWORD)((PDH_CVERSION_WIN50) + 0x0003))
25
26	#define IsSuccessSeverity(ErrorCode) ((!((DWORD)(ErrorCode) & 0xC0000000)) ? TRUE : FALSE)
27	#define IsInformationalSeverity(ErrorCode) ((((DWORD)(ErrorCode) & 0xC0000000)==(DWORD)0x40000000) ? TRUE : FALSE)
28	#define IsWarningSeverity(ErrorCode) ((((DWORD)(ErrorCode) & 0xC0000000)==(DWORD)0x80000000) ? TRUE : FALSE)
29	#define IsErrorSeverity(ErrorCode) ((((DWORD)(ErrorCode) & 0xC0000000)==(DWORD)0xC0000000) ? TRUE : FALSE)
30
31	#define MAX_COUNTER_PATH 256
32
33	#define PDH_MAX_COUNTER_NAME 1024
34	#define PDH_MAX_INSTANCE_NAME 1024
35	#define PDH_MAX_COUNTER_PATH 2048
36	#define PDH_MAX_DATASOURCE_PATH 1024
37
38	  typedef HANDLE PDH_HCOUNTER;
39	  typedef HANDLE PDH_HQUERY;
40	  typedef HANDLE PDH_HLOG;
41
42	  typedef PDH_HCOUNTER HCOUNTER;
43	  typedef PDH_HQUERY HQUERY;
44	#ifndef _LMHLOGDEFINED_
45	  typedef PDH_HLOG HLOG;
46	#endif
47
48	#ifdef INVALID_HANDLE_VALUE
49	#undef INVALID_HANDLE_VALUE
50	#define INVALID_HANDLE_VALUE ((HANDLE)((LONG_PTR)-1))
51	#endif
52
53	#define H_REALTIME_DATASOURCE NULL
54	#define H_WBEM_DATASOURCE INVALID_HANDLE_VALUE
55
56	  typedef struct _PDH_RAW_COUNTER {
57	    DWORD CStatus;
58	    FILETIME TimeStamp;
59	    LONGLONG FirstValue;
60	    LONGLONG SecondValue;
61	    DWORD MultiCount;
62	  } PDH_RAW_COUNTER,*PPDH_RAW_COUNTER;
63
64	  typedef struct _PDH_RAW_COUNTER_ITEM_A {
65	    LPSTR szName;
66	    PDH_RAW_COUNTER RawValue;
67	  } PDH_RAW_COUNTER_ITEM_A,*PPDH_RAW_COUNTER_ITEM_A;
68
69	  typedef struct _PDH_RAW_COUNTER_ITEM_W {
70	    LPWSTR szName;
71	    PDH_RAW_COUNTER RawValue;
72	  } PDH_RAW_COUNTER_ITEM_W,*PPDH_RAW_COUNTER_ITEM_W;
73
74	  typedef struct _PDH_FMT_COUNTERVALUE {
75	    DWORD CStatus;
76	    __C89_NAMELESS union {
77	      LONG longValue;
78	      double doubleValue;
79	      LONGLONG largeValue;
80	      LPCSTR AnsiStringValue;
81	      LPCWSTR WideStringValue;
82	    };
83	  } PDH_FMT_COUNTERVALUE,*PPDH_FMT_COUNTERVALUE;
84
85	  typedef struct _PDH_FMT_COUNTERVALUE_ITEM_A {
86	    LPSTR szName;
87	    PDH_FMT_COUNTERVALUE FmtValue;
88	  } PDH_FMT_COUNTERVALUE_ITEM_A,*PPDH_FMT_COUNTERVALUE_ITEM_A;
89
90	  typedef struct _PDH_FMT_COUNTERVALUE_ITEM_W {
91	    LPWSTR szName;
92	    PDH_FMT_COUNTERVALUE FmtValue;
93	  } PDH_FMT_COUNTERVALUE_ITEM_W,*PPDH_FMT_COUNTERVALUE_ITEM_W;
94
95	  typedef struct _PDH_STATISTICS {
96	    DWORD dwFormat;
97	    DWORD count;
98	    PDH_FMT_COUNTERVALUE min;
99	    PDH_FMT_COUNTERVALUE max;
100	    PDH_FMT_COUNTERVALUE mean;
101	  } PDH_STATISTICS,*PPDH_STATISTICS;
102
103	  typedef struct _PDH_COUNTER_PATH_ELEMENTS_A {
104	    LPSTR szMachineName;
105	    LPSTR szObjectName;
106	    LPSTR szInstanceName;
107	    LPSTR szParentInstance;
108	    DWORD dwInstanceIndex;
109	    LPSTR szCounterName;
110	  } PDH_COUNTER_PATH_ELEMENTS_A,*PPDH_COUNTER_PATH_ELEMENTS_A;
111
112	  typedef struct _PDH_COUNTER_PATH_ELEMENTS_W {
113	    LPWSTR szMachineName;
114	    LPWSTR szObjectName;
115	    LPWSTR szInstanceName;
116	    LPWSTR szParentInstance;
117	    DWORD dwInstanceIndex;
118	    LPWSTR szCounterName;
119	  } PDH_COUNTER_PATH_ELEMENTS_W,*PPDH_COUNTER_PATH_ELEMENTS_W;
120
121	  typedef struct _PDH_DATA_ITEM_PATH_ELEMENTS_A {
122	    LPSTR szMachineName;
123	    GUID ObjectGUID;
124	    DWORD dwItemId;
125	    LPSTR szInstanceName;
126	  } PDH_DATA_ITEM_PATH_ELEMENTS_A,*PPDH_DATA_ITEM_PATH_ELEMENTS_A;
127
128	  typedef struct _PDH_DATA_ITEM_PATH_ELEMENTS_W {
129	    LPWSTR szMachineName;
130	    GUID ObjectGUID;
131	    DWORD dwItemId;
132	    LPWSTR szInstanceName;
133	  } PDH_DATA_ITEM_PATH_ELEMENTS_W,*PPDH_DATA_ITEM_PATH_ELEMENTS_W;
134
135	  typedef struct _PDH_COUNTER_INFO_A {
136	    DWORD dwLength;
137	    DWORD dwType;
138	    DWORD CVersion;
139	    DWORD CStatus;
140	    LONG lScale;
141	    LONG lDefaultScale;
142	    DWORD_PTR dwUserData;
143	    DWORD_PTR dwQueryUserData;
144	    LPSTR szFullPath;
145	    __C89_NAMELESS union {
146	      PDH_DATA_ITEM_PATH_ELEMENTS_A DataItemPath;
147	      PDH_COUNTER_PATH_ELEMENTS_A CounterPath;
148	      __C89_NAMELESS struct {
149	        LPSTR szMachineName;
150	        LPSTR szObjectName;
151	        LPSTR szInstanceName;
152	        LPSTR szParentInstance;
153	        DWORD dwInstanceIndex;
154	        LPSTR szCounterName;
155	      };
156	    };
157	    LPSTR szExplainText;
158	    DWORD DataBuffer[1];
159	  } PDH_COUNTER_INFO_A,*PPDH_COUNTER_INFO_A;
160
161	  typedef struct _PDH_COUNTER_INFO_W {
162	    DWORD dwLength;
163	    DWORD dwType;
164	    DWORD CVersion;
165	    DWORD CStatus;
166	    LONG lScale;
167	    LONG lDefaultScale;
168	    DWORD_PTR dwUserData;
169	    DWORD_PTR dwQueryUserData;
170	    LPWSTR szFullPath;
171	    __C89_NAMELESS union {
172	      PDH_DATA_ITEM_PATH_ELEMENTS_W DataItemPath;
173	      PDH_COUNTER_PATH_ELEMENTS_W CounterPath;
174	      __C89_NAMELESS struct {
175	        LPWSTR szMachineName;
176	        LPWSTR szObjectName;
177	        LPWSTR szInstanceName;
178	        LPWSTR szParentInstance;
179	        DWORD dwInstanceIndex;
180	        LPWSTR szCounterName;
181	      };
182	    };
183	    LPWSTR szExplainText;
184	    DWORD DataBuffer[1];
185	  } PDH_COUNTER_INFO_W,*PPDH_COUNTER_INFO_W;
186
187	  typedef struct _PDH_TIME_INFO {
188	    LONGLONG StartTime;
189	    LONGLONG EndTime;
190	    DWORD SampleCount;
191	  } PDH_TIME_INFO,*PPDH_TIME_INFO;
192
193	  typedef struct _PDH_RAW_LOG_RECORD {
194	    DWORD dwStructureSize;
195	    DWORD dwRecordType;
196	    DWORD dwItems;
197	    UCHAR RawBytes[1];
198	  } PDH_RAW_LOG_RECORD,*PPDH_RAW_LOG_RECORD;
199
200	  typedef struct _PDH_LOG_SERVICE_QUERY_INFO_A {
201	    DWORD dwSize;
202	    DWORD dwFlags;
203	    DWORD dwLogQuota;
204	    LPSTR szLogFileCaption;
205	    LPSTR szDefaultDir;
206	    LPSTR szBaseFileName;
207	    DWORD dwFileType;
208	    DWORD dwReserved;
209	    __C89_NAMELESS union {
210	      __C89_NAMELESS struct {
211	        DWORD PdlAutoNameInterval;
212	        DWORD PdlAutoNameUnits;
213	        LPSTR PdlCommandFilename;
214	        LPSTR PdlCounterList;
215	        DWORD PdlAutoNameFormat;
216	        DWORD PdlSampleInterval;
217	        FILETIME PdlLogStartTime;
218	        FILETIME PdlLogEndTime;
219	      };
220	      __C89_NAMELESS struct {
221	        DWORD TlNumberOfBuffers;
222	        DWORD TlMinimumBuffers;
223	        DWORD TlMaximumBuffers;
224	        DWORD TlFreeBuffers;
225	        DWORD TlBufferSize;
226	        DWORD TlEventsLost;
227	        DWORD TlLoggerThreadId;
228	        DWORD TlBuffersWritten;
229	        DWORD TlLogHandle;
230	        LPSTR TlLogFileName;
231	      };
232	    };
233	  } PDH_LOG_SERVICE_QUERY_INFO_A,*PPDH_LOG_SERVICE_QUERY_INFO_A;
234
235	  typedef struct _PDH_LOG_SERVICE_QUERY_INFO_W {
236	    DWORD dwSize;
237	    DWORD dwFlags;
238	    DWORD dwLogQuota;
239	    LPWSTR szLogFileCaption;
240	    LPWSTR szDefaultDir;
241	    LPWSTR szBaseFileName;
242	    DWORD dwFileType;
243	    DWORD dwReserved;
244	    __C89_NAMELESS union {
245	      __C89_NAMELESS struct {
246	        DWORD PdlAutoNameInterval;
247	        DWORD PdlAutoNameUnits;
248	        LPWSTR PdlCommandFilename;
249	        LPWSTR PdlCounterList;
250	        DWORD PdlAutoNameFormat;
251	        DWORD PdlSampleInterval;
252	        FILETIME PdlLogStartTime;
253	        FILETIME PdlLogEndTime;
254	      };
255	      __C89_NAMELESS struct {
256	        DWORD TlNumberOfBuffers;
257	        DWORD TlMinimumBuffers;
258	        DWORD TlMaximumBuffers;
259	        DWORD TlFreeBuffers;
260	        DWORD TlBufferSize;
261	        DWORD TlEventsLost;
262	        DWORD TlLoggerThreadId;
263	        DWORD TlBuffersWritten;
264	        DWORD TlLogHandle;
265	        LPWSTR TlLogFileName;
266	      };
267	    };
268	  } PDH_LOG_SERVICE_QUERY_INFO_W,*PPDH_LOG_SERVICE_QUERY_INFO_W;
269
270	#define MAX_TIME_VALUE ((LONGLONG) 0x7FFFFFFFFFFFFFFF)
271	#define MIN_TIME_VALUE ((LONGLONG) 0)
272
273	  PDH_FUNCTION PdhGetDllVersion(LPDWORD lpdwVersion);
274	  PDH_FUNCTION PdhOpenQueryW(LPCWSTR szDataSource,DWORD_PTR dwUserData,PDH_HQUERY *phQuery);
275	  PDH_FUNCTION PdhOpenQueryA(LPCSTR szDataSource,DWORD_PTR dwUserData,PDH_HQUERY *phQuery);
276	  PDH_FUNCTION PdhAddCounterW(PDH_HQUERY hQuery,LPCWSTR szFullCounterPath,DWORD_PTR dwUserData,PDH_HCOUNTER *phCounter);
277	  PDH_FUNCTION PdhAddCounterA(PDH_HQUERY hQuery,LPCSTR szFullCounterPath,DWORD_PTR dwUserData,PDH_HCOUNTER *phCounter);
278	  PDH_FUNCTION PdhRemoveCounter(PDH_HCOUNTER hCounter);
279	  PDH_FUNCTION PdhCollectQueryData(PDH_HQUERY hQuery);
280	  PDH_FUNCTION PdhCloseQuery(PDH_HQUERY hQuery);
281	  PDH_FUNCTION PdhGetFormattedCounterValue(PDH_HCOUNTER hCounter,DWORD dwFormat,LPDWORD lpdwType,PPDH_FMT_COUNTERVALUE pValue);
282	  PDH_FUNCTION PdhGetFormattedCounterArrayA(PDH_HCOUNTER hCounter,DWORD dwFormat,LPDWORD lpdwBufferSize,LPDWORD lpdwItemCount,PPDH_FMT_COUNTERVALUE_ITEM_A ItemBuffer);
283	  PDH_FUNCTION PdhGetFormattedCounterArrayW(PDH_HCOUNTER hCounter,DWORD dwFormat,LPDWORD lpdwBufferSize,LPDWORD lpdwItemCount,PPDH_FMT_COUNTERVALUE_ITEM_W ItemBuffer);
284
285	#define PDH_FMT_RAW ((DWORD) 0x00000010)
286	#define PDH_FMT_ANSI ((DWORD) 0x00000020)
287	#define PDH_FMT_UNICODE ((DWORD) 0x00000040)
288	#define PDH_FMT_LONG ((DWORD) 0x00000100)
289	#define PDH_FMT_DOUBLE ((DWORD) 0x00000200)
290	#define PDH_FMT_LARGE ((DWORD) 0x00000400)
291	#define PDH_FMT_NOSCALE ((DWORD) 0x00001000)
292	#define PDH_FMT_1000 ((DWORD) 0x00002000)
293	#define PDH_FMT_NODATA ((DWORD) 0x00004000)
294	#define PDH_FMT_NOCAP100 ((DWORD) 0x00008000)
295	#define PERF_DETAIL_COSTLY ((DWORD) 0x00010000)
296	#define PERF_DETAIL_STANDARD ((DWORD) 0x0000FFFF)
297
298	  PDH_FUNCTION PdhGetRawCounterValue(PDH_HCOUNTER hCounter,LPDWORD lpdwType,PPDH_RAW_COUNTER pValue);
299	  PDH_FUNCTION PdhGetRawCounterArrayA(PDH_HCOUNTER hCounter,LPDWORD lpdwBufferSize,LPDWORD lpdwItemCount,PPDH_RAW_COUNTER_ITEM_A ItemBuffer);
300	  PDH_FUNCTION PdhGetRawCounterArrayW(PDH_HCOUNTER hCounter,LPDWORD lpdwBufferSize,LPDWORD lpdwItemCount,PPDH_RAW_COUNTER_ITEM_W ItemBuffer);
301	  PDH_FUNCTION PdhCalculateCounterFromRawValue(PDH_HCOUNTER hCounter,DWORD dwFormat,PPDH_RAW_COUNTER rawValue1,PPDH_RAW_COUNTER rawValue2,PPDH_FMT_COUNTERVALUE fmtValue);
302	  PDH_FUNCTION PdhComputeCounterStatistics(PDH_HCOUNTER hCounter,DWORD dwFormat,DWORD dwFirstEntry,DWORD dwNumEntries,PPDH_RAW_COUNTER lpRawValueArray,PPDH_STATISTICS data);
303	  PDH_FUNCTION PdhGetCounterInfoW(PDH_HCOUNTER hCounter,BOOLEAN bRetrieveExplainText,LPDWORD pdwBufferSize,PPDH_COUNTER_INFO_W lpBuffer);
304	  PDH_FUNCTION PdhGetCounterInfoA(PDH_HCOUNTER hCounter,BOOLEAN bRetrieveExplainText,LPDWORD pdwBufferSize,PPDH_COUNTER_INFO_A lpBuffer);
305
306	#define PDH_MAX_SCALE (__MSABI_LONG(7))
307	#define PDH_MIN_SCALE (__MSABI_LONG(-7))
308
309	  PDH_FUNCTION PdhSetCounterScaleFactor(PDH_HCOUNTER hCounter,LONG lFactor);
310	  PDH_FUNCTION PdhConnectMachineW(LPCWSTR szMachineName);
311	  PDH_FUNCTION PdhConnectMachineA(LPCSTR szMachineName);
312	  PDH_FUNCTION PdhEnumMachinesW(LPCWSTR szDataSource,LPWSTR mszMachineList,LPDWORD pcchBufferSize);
313	  PDH_FUNCTION PdhEnumMachinesA(LPCSTR szDataSource,LPSTR mszMachineList,LPDWORD pcchBufferSize);
314	  PDH_FUNCTION PdhEnumObjectsW(LPCWSTR szDataSource,LPCWSTR szMachineName,LPWSTR mszObjectList,LPDWORD pcchBufferSize,DWORD dwDetailLevel,WINBOOL bRefresh);
315	  PDH_FUNCTION PdhEnumObjectsA(LPCSTR szDataSource,LPCSTR szMachineName,LPSTR mszObjectList,LPDWORD pcchBufferSize,DWORD dwDetailLevel,WINBOOL bRefresh);
316	  PDH_FUNCTION PdhEnumObjectItemsW(LPCWSTR szDataSource,LPCWSTR szMachineName,LPCWSTR szObjectName,LPWSTR mszCounterList,LPDWORD pcchCounterListLength,LPWSTR mszInstanceList,LPDWORD pcchInstanceListLength,DWORD dwDetailLevel,DWORD dwFlags);
317	  PDH_FUNCTION PdhEnumObjectItemsA(LPCSTR szDataSource,LPCSTR szMachineName,LPCSTR szObjectName,LPSTR mszCounterList,LPDWORD pcchCounterListLength,LPSTR mszInstanceList,LPDWORD pcchInstanceListLength,DWORD dwDetailLevel,DWORD dwFlags);
318
319	#define PDH_OBJECT_HAS_INSTANCES ((DWORD) 0x00000001)
320
321	  PDH_FUNCTION PdhMakeCounterPathW(PPDH_COUNTER_PATH_ELEMENTS_W pCounterPathElements,LPWSTR szFullPathBuffer,LPDWORD pcchBufferSize,DWORD dwFlags);
322	  PDH_FUNCTION PdhMakeCounterPathA(PPDH_COUNTER_PATH_ELEMENTS_A pCounterPathElements,LPSTR szFullPathBuffer,LPDWORD pcchBufferSize,DWORD dwFlags);
323	  PDH_FUNCTION PdhParseCounterPathW(LPCWSTR szFullPathBuffer,PPDH_COUNTER_PATH_ELEMENTS_W pCounterPathElements,LPDWORD pdwBufferSize,DWORD dwFlags);
324	  PDH_FUNCTION PdhParseCounterPathA(LPCSTR szFullPathBuffer,PPDH_COUNTER_PATH_ELEMENTS_A pCounterPathElements,LPDWORD pdwBufferSize,DWORD dwFlags);
325
326	#define PDH_PATH_WBEM_RESULT ((DWORD) 0x00000001)
327	#define PDH_PATH_WBEM_INPUT ((DWORD) 0x00000002)
328
329	#define PDH_PATH_LANG_FLAGS(LangId,Flags) ((DWORD)(((LangId & 0x0000FFFF) << 16) | (Flags & 0x0000FFFF)))
330
331	  PDH_FUNCTION PdhParseInstanceNameW(LPCWSTR szInstanceString,LPWSTR szInstanceName,LPDWORD pcchInstanceNameLength,LPWSTR szParentName,LPDWORD pcchParentNameLength,LPDWORD lpIndex);
332	  PDH_FUNCTION PdhParseInstanceNameA(LPCSTR szInstanceString,LPSTR szInstanceName,LPDWORD pcchInstanceNameLength,LPSTR szParentName,LPDWORD pcchParentNameLength,LPDWORD lpIndex);
333	  PDH_FUNCTION PdhValidatePathW(LPCWSTR szFullPathBuffer);
334	  PDH_FUNCTION PdhValidatePathA(LPCSTR szFullPathBuffer);
335	  PDH_FUNCTION PdhGetDefaultPerfObjectW(LPCWSTR szDataSource,LPCWSTR szMachineName,LPWSTR szDefaultObjectName,LPDWORD pcchBufferSize);
336	  PDH_FUNCTION PdhGetDefaultPerfObjectA(LPCSTR szDataSource,LPCSTR szMachineName,LPSTR szDefaultObjectName,LPDWORD pcchBufferSize);
337	  PDH_FUNCTION PdhGetDefaultPerfCounterW(LPCWSTR szDataSource,LPCWSTR szMachineName,LPCWSTR szObjectName,LPWSTR szDefaultCounterName,LPDWORD pcchBufferSize);
338	  PDH_FUNCTION PdhGetDefaultPerfCounterA(LPCSTR szDataSource,LPCSTR szMachineName,LPCSTR szObjectName,LPSTR szDefaultCounterName,LPDWORD pcchBufferSize);
339
340	  typedef PDH_STATUS (WINAPI *CounterPathCallBack)(DWORD_PTR);
341
342	  typedef struct _BrowseDlgConfig_HW {
343	    DWORD bIncludeInstanceIndex : 1,bSingleCounterPerAdd : 1,bSingleCounterPerDialog : 1,bLocalCountersOnly : 1,bWildCardInstances : 1,bHideDetailBox : 1,bInitializePath : 1,bDisableMachineSelection : 1,bIncludeCostlyObjects : 1,bShowObjectBrowser : 1,bReserved : 22;
344	    HWND hWndOwner;
345	    PDH_HLOG hDataSource;
346	    LPWSTR szReturnPathBuffer;
347	    DWORD cchReturnPathLength;
348	    CounterPathCallBack pCallBack;
349	    DWORD_PTR dwCallBackArg;
350	    PDH_STATUS CallBackStatus;
351	    DWORD dwDefaultDetailLevel;
352	    LPWSTR szDialogBoxCaption;
353	  } PDH_BROWSE_DLG_CONFIG_HW,*PPDH_BROWSE_DLG_CONFIG_HW;
354
355	  typedef struct _BrowseDlgConfig_HA {
356	    DWORD bIncludeInstanceIndex : 1,bSingleCounterPerAdd : 1,bSingleCounterPerDialog : 1,bLocalCountersOnly : 1,bWildCardInstances : 1,bHideDetailBox : 1,bInitializePath : 1,bDisableMachineSelection : 1,bIncludeCostlyObjects : 1,bShowObjectBrowser : 1,bReserved:22;
357	    HWND hWndOwner;
358	    PDH_HLOG hDataSource;
359	    LPSTR szReturnPathBuffer;
360	    DWORD cchReturnPathLength;
361	    CounterPathCallBack pCallBack;
362	    DWORD_PTR dwCallBackArg;
363	    PDH_STATUS CallBackStatus;
364	    DWORD dwDefaultDetailLevel;
365	    LPSTR szDialogBoxCaption;
366	  } PDH_BROWSE_DLG_CONFIG_HA,*PPDH_BROWSE_DLG_CONFIG_HA;
367
368	  typedef struct _BrowseDlgConfig_W {
369	    DWORD bIncludeInstanceIndex : 1,bSingleCounterPerAdd : 1,bSingleCounterPerDialog : 1,bLocalCountersOnly : 1,bWildCardInstances : 1,bHideDetailBox : 1,bInitializePath : 1,bDisableMachineSelection : 1,bIncludeCostlyObjects : 1,bShowObjectBrowser : 1,bReserved:22;
370	    HWND hWndOwner;
371	    LPWSTR szDataSource;
372	    LPWSTR szReturnPathBuffer;
373	    DWORD cchReturnPathLength;
374	    CounterPathCallBack pCallBack;
375	    DWORD_PTR dwCallBackArg;
376	    PDH_STATUS CallBackStatus;
377	    DWORD dwDefaultDetailLevel;
378	    LPWSTR szDialogBoxCaption;
379	  } PDH_BROWSE_DLG_CONFIG_W,*PPDH_BROWSE_DLG_CONFIG_W;
380
381	  typedef struct _BrowseDlgConfig_A {
382	    DWORD bIncludeInstanceIndex : 1,bSingleCounterPerAdd : 1,bSingleCounterPerDialog : 1,bLocalCountersOnly : 1,bWildCardInstances : 1,bHideDetailBox : 1,bInitializePath : 1,bDisableMachineSelection : 1,bIncludeCostlyObjects : 1,bShowObjectBrowser : 1,bReserved:22;
383	    HWND hWndOwner;
384	    LPSTR szDataSource;
385	    LPSTR szReturnPathBuffer;
386	    DWORD cchReturnPathLength;
387	    CounterPathCallBack pCallBack;
388	    DWORD_PTR dwCallBackArg;
389	    PDH_STATUS CallBackStatus;
390	    DWORD dwDefaultDetailLevel;
391	    LPSTR szDialogBoxCaption;
392	  } PDH_BROWSE_DLG_CONFIG_A,*PPDH_BROWSE_DLG_CONFIG_A;
393
394	  PDH_FUNCTION PdhBrowseCountersW(PPDH_BROWSE_DLG_CONFIG_W pBrowseDlgData);
395	  PDH_FUNCTION PdhBrowseCountersA(PPDH_BROWSE_DLG_CONFIG_A pBrowseDlgData);
396	  PDH_FUNCTION PdhExpandCounterPathW(LPCWSTR szWildCardPath,LPWSTR mszExpandedPathList,LPDWORD pcchPathListLength);
397	  PDH_FUNCTION PdhExpandCounterPathA(LPCSTR szWildCardPath,LPSTR mszExpandedPathList,LPDWORD pcchPathListLength);
398	  PDH_FUNCTION PdhLookupPerfNameByIndexW(LPCWSTR szMachineName,DWORD dwNameIndex,LPWSTR szNameBuffer,LPDWORD pcchNameBufferSize);
399	  PDH_FUNCTION PdhLookupPerfNameByIndexA(LPCSTR szMachineName,DWORD dwNameIndex,LPSTR szNameBuffer,LPDWORD pcchNameBufferSize);
400	  PDH_FUNCTION PdhLookupPerfIndexByNameW(LPCWSTR szMachineName,LPCWSTR szNameBuffer,LPDWORD pdwIndex);
401	  PDH_FUNCTION PdhLookupPerfIndexByNameA(LPCSTR szMachineName,LPCSTR szNameBuffer,LPDWORD pdwIndex);
402
403	#define PDH_NOEXPANDCOUNTERS 1
404	#define PDH_NOEXPANDINSTANCES 2
405	#define PDH_REFRESHCOUNTERS 4
406
407	  PDH_FUNCTION PdhExpandWildCardPathA(LPCSTR szDataSource,LPCSTR szWildCardPath,LPSTR mszExpandedPathList,LPDWORD pcchPathListLength,DWORD dwFlags);
408	  PDH_FUNCTION PdhExpandWildCardPathW(LPCWSTR szDataSource,LPCWSTR szWildCardPath,LPWSTR mszExpandedPathList,LPDWORD pcchPathListLength,DWORD dwFlags);
409
410	#define PDH_LOG_READ_ACCESS ((DWORD) 0x00010000)
411	#define PDH_LOG_WRITE_ACCESS ((DWORD) 0x00020000)
412	#define PDH_LOG_UPDATE_ACCESS ((DWORD) 0x00040000)
413	#define PDH_LOG_ACCESS_MASK ((DWORD) 0x000F0000)
414
415	#define PDH_LOG_CREATE_NEW ((DWORD) 0x00000001)
416	#define PDH_LOG_CREATE_ALWAYS ((DWORD) 0x00000002)
417	#define PDH_LOG_OPEN_ALWAYS ((DWORD) 0x00000003)
418	#define PDH_LOG_OPEN_EXISTING ((DWORD) 0x00000004)
419	#define PDH_LOG_CREATE_MASK ((DWORD) 0x0000000F)
420
421	#define PDH_LOG_OPT_USER_STRING ((DWORD) 0x01000000)
422	#define PDH_LOG_OPT_CIRCULAR ((DWORD) 0x02000000)
423	#define PDH_LOG_OPT_MAX_IS_BYTES ((DWORD) 0x04000000)
424	#define PDH_LOG_OPT_APPEND ((DWORD) 0x08000000)
425	#define PDH_LOG_OPT_MASK ((DWORD) 0x0F000000)
426
427	#define PDH_LOG_TYPE_UNDEFINED 0
428	#define PDH_LOG_TYPE_CSV 1
429	#define PDH_LOG_TYPE_TSV 2
430
431	#define PDH_LOG_TYPE_TRACE_KERNEL 4
432	#define PDH_LOG_TYPE_TRACE_GENERIC 5
433	#define PDH_LOG_TYPE_PERFMON 6
434	#define PDH_LOG_TYPE_SQL 7
435	#define PDH_LOG_TYPE_BINARY 8
436
437	  PDH_FUNCTION PdhOpenLogW(LPCWSTR szLogFileName,DWORD dwAccessFlags,LPDWORD lpdwLogType,PDH_HQUERY hQuery,DWORD dwMaxSize,LPCWSTR szUserCaption,PDH_HLOG *phLog);
438	  PDH_FUNCTION PdhOpenLogA(LPCSTR szLogFileName,DWORD dwAccessFlags,LPDWORD lpdwLogType,PDH_HQUERY hQuery,DWORD dwMaxSize,LPCSTR szUserCaption,PDH_HLOG *phLog);
439	  PDH_FUNCTION PdhUpdateLogW(PDH_HLOG hLog,LPCWSTR szUserString);
440	  PDH_FUNCTION PdhUpdateLogA(PDH_HLOG hLog,LPCSTR szUserString);
441	  PDH_FUNCTION PdhUpdateLogFileCatalog(PDH_HLOG hLog);
442	  PDH_FUNCTION PdhGetLogFileSize(PDH_HLOG hLog,LONGLONG *llSize);
443	  PDH_FUNCTION PdhCloseLog(PDH_HLOG hLog,DWORD dwFlags);
444
445	#define PDH_FLAGS_CLOSE_QUERY ((DWORD) 0x00000001)
446	#define PDH_FLAGS_FILE_BROWSER_ONLY ((DWORD) 0x00000001)
447
448	  PDH_FUNCTION PdhSelectDataSourceW(HWND hWndOwner,DWORD dwFlags,LPWSTR szDataSource,LPDWORD pcchBufferLength);
449	  PDH_FUNCTION PdhSelectDataSourceA(HWND hWndOwner,DWORD dwFlags,LPSTR szDataSource,LPDWORD pcchBufferLength);
450	  WINBOOL PdhIsRealTimeQuery(PDH_HQUERY hQuery);
451	  PDH_FUNCTION PdhSetQueryTimeRange(PDH_HQUERY hQuery,PPDH_TIME_INFO pInfo);
452	  PDH_FUNCTION PdhGetDataSourceTimeRangeW(LPCWSTR szDataSource,LPDWORD pdwNumEntries,PPDH_TIME_INFO pInfo,LPDWORD pdwBufferSize);
453	  PDH_FUNCTION PdhGetDataSourceTimeRangeA(LPCSTR szDataSource,LPDWORD pdwNumEntries,PPDH_TIME_INFO pInfo,LPDWORD dwBufferSize);
454	  PDH_FUNCTION PdhCollectQueryDataEx(PDH_HQUERY hQuery,DWORD dwIntervalTime,HANDLE hNewDataEvent);
455	  PDH_FUNCTION PdhFormatFromRawValue(DWORD dwCounterType,DWORD dwFormat,LONGLONG *pTimeBase,PPDH_RAW_COUNTER pRawValue1,PPDH_RAW_COUNTER pRawValue2,PPDH_FMT_COUNTERVALUE pFmtValue);
456	  PDH_FUNCTION PdhGetCounterTimeBase(PDH_HCOUNTER hCounter,LONGLONG *pTimeBase);
457	  PDH_FUNCTION PdhReadRawLogRecord(PDH_HLOG hLog,FILETIME ftRecord,PPDH_RAW_LOG_RECORD pRawLogRecord,LPDWORD pdwBufferLength);
458
459	#define DATA_SOURCE_REGISTRY ((DWORD) 0x00000001)
460	#define DATA_SOURCE_LOGFILE ((DWORD) 0x00000002)
461	#define DATA_SOURCE_WBEM ((DWORD) 0x00000004)
462
463	  PDH_FUNCTION PdhSetDefaultRealTimeDataSource(DWORD dwDataSourceId);
464	  PDH_FUNCTION PdhBindInputDataSourceW(PDH_HLOG *phDataSource,LPCWSTR LogFileNameList);
465	  PDH_FUNCTION PdhBindInputDataSourceA(PDH_HLOG *phDataSource,LPCSTR LogFileNameList);
466	  PDH_FUNCTION PdhOpenQueryH(PDH_HLOG hDataSource,DWORD_PTR dwUserData,PDH_HQUERY *phQuery);
467	  PDH_FUNCTION PdhEnumMachinesHW(PDH_HLOG hDataSource,LPWSTR mszMachineList,LPDWORD pcchBufferSize);
468	  PDH_FUNCTION PdhEnumMachinesHA(PDH_HLOG hDataSource,LPSTR mszMachineList,LPDWORD pcchBufferSize);
469	  PDH_FUNCTION PdhEnumObjectsHW(PDH_HLOG hDataSource,LPCWSTR szMachineName,LPWSTR mszObjectList,LPDWORD pcchBufferSize,DWORD dwDetailLevel,WINBOOL bRefresh);
470	  PDH_FUNCTION PdhEnumObjectsHA(PDH_HLOG hDataSource,LPCSTR szMachineName,LPSTR mszObjectList,LPDWORD pcchBufferSize,DWORD dwDetailLevel,WINBOOL bRefresh);
471	  PDH_FUNCTION PdhEnumObjectItemsHW(PDH_HLOG hDataSource,LPCWSTR szMachineName,LPCWSTR szObjectName,LPWSTR mszCounterList,LPDWORD pcchCounterListLength,LPWSTR mszInstanceList,LPDWORD pcchInstanceListLength,DWORD dwDetailLevel,DWORD dwFlags);
472	  PDH_FUNCTION PdhEnumObjectItemsHA(PDH_HLOG hDataSource,LPCSTR szMachineName,LPCSTR szObjectName,LPSTR mszCounterList,LPDWORD pcchCounterListLength,LPSTR mszInstanceList,LPDWORD pcchInstanceListLength,DWORD dwDetailLevel,DWORD dwFlags);
473	  PDH_FUNCTION PdhExpandWildCardPathHW(PDH_HLOG hDataSource,LPCWSTR szWildCardPath,LPWSTR mszExpandedPathList,LPDWORD pcchPathListLength,DWORD dwFlags);
474	  PDH_FUNCTION PdhExpandWildCardPathHA(PDH_HLOG hDataSource,LPCSTR szWildCardPath,LPSTR mszExpandedPathList,LPDWORD pcchPathListLength,DWORD dwFlags);
475	  PDH_FUNCTION PdhGetDataSourceTimeRangeH(PDH_HLOG hDataSource,LPDWORD pdwNumEntries,PPDH_TIME_INFO pInfo,LPDWORD pdwBufferSize);
476	  PDH_FUNCTION PdhGetDefaultPerfObjectHW(PDH_HLOG hDataSource,LPCWSTR szMachineName,LPWSTR szDefaultObjectName,LPDWORD pcchBufferSize);
477	  PDH_FUNCTION PdhGetDefaultPerfObjectHA(PDH_HLOG hDataSource,LPCSTR szMachineName,LPSTR szDefaultObjectName,LPDWORD pcchBufferSize);
478	  PDH_FUNCTION PdhGetDefaultPerfCounterHW(PDH_HLOG hDataSource,LPCWSTR szMachineName,LPCWSTR szObjectName,LPWSTR szDefaultCounterName,LPDWORD pcchBufferSize);
479	  PDH_FUNCTION PdhGetDefaultPerfCounterHA(PDH_HLOG hDataSource,LPCSTR szMachineName,LPCSTR szObjectName,LPSTR szDefaultCounterName,LPDWORD pcchBufferSize);
480	  PDH_FUNCTION PdhBrowseCountersHW(PPDH_BROWSE_DLG_CONFIG_HW pBrowseDlgData);
481	  PDH_FUNCTION PdhBrowseCountersHA(PPDH_BROWSE_DLG_CONFIG_HA pBrowseDlgData);
482	  PDH_FUNCTION PdhVerifySQLDBW(LPCWSTR szDataSource);
483	  PDH_FUNCTION PdhVerifySQLDBA(LPCSTR szDataSource);
484	  PDH_FUNCTION PdhCreateSQLTablesW(LPCWSTR szDataSource);
485	  PDH_FUNCTION PdhCreateSQLTablesA(LPCSTR szDataSource);
486	  PDH_FUNCTION PdhEnumLogSetNamesW(LPCWSTR szDataSource,LPWSTR mszDataSetNameList,LPDWORD pcchBufferLength);
487	  PDH_FUNCTION PdhEnumLogSetNamesA(LPCSTR szDataSource,LPSTR mszDataSetNameList,LPDWORD pcchBufferLength);
488	  PDH_FUNCTION PdhGetLogSetGUID(PDH_HLOG hLog,GUID *pGuid,int *pRunId);
489	  PDH_FUNCTION PdhSetLogSetRunID(PDH_HLOG hLog,int RunId);
490
491	#if defined(UNICODE)
492	#ifndef _UNICODE
493	#define _UNICODE
494	#endif
495	#endif
496
497	#if defined(_UNICODE)
498	#if !defined(UNICODE)
499	#define UNICODE
500	#endif
501	#endif
502
503	#define PDH_COUNTER_INFO __MINGW_NAME_UAW(PDH_COUNTER_INFO)
504	#define PPDH_COUNTER_INFO __MINGW_NAME_UAW(PPDH_COUNTER_INFO)
505	#define PDH_COUNTER_PATH_ELEMENTS __MINGW_NAME_UAW(PDH_COUNTER_PATH_ELEMENTS)
506	#define PPDH_COUNTER_PATH_ELEMENTS __MINGW_NAME_UAW(PPDH_COUNTER_PATH_ELEMENTS)
507	#define PDH_BROWSE_DLG_CONFIG __MINGW_NAME_UAW(PDH_BROWSE_DLG_CONFIG)
508	#define PPDH_BROWSE_DLG_CONFIG __MINGW_NAME_UAW(PPDH_BROWSE_DLG_CONFIG)
509	#define PDH_FMT_COUNTERVALUE_ITEM __MINGW_NAME_UAW(PDH_FMT_COUNTERVALUE_ITEM)
510	#define PPDH_FMT_COUNTERVALUE_ITEM __MINGW_NAME_UAW(PPDH_FMT_COUNTERVALUE_ITEM)
511	#define PDH_RAW_COUNTER_ITEM __MINGW_NAME_UAW(PDH_RAW_COUNTER_ITEM)
512	#define PPDH_RAW_COUNTER_ITEM __MINGW_NAME_UAW(PPDH_RAW_COUNTER_ITEM)
513	#define PDH_LOG_SERVICE_QUERY_INFO __MINGW_NAME_UAW(PDH_LOG_SERVICE_QUERY_INFO)
514	#define PPDH_LOG_SERVICE_QUERY_INFO __MINGW_NAME_UAW(PPDH_LOG_SERVICE_QUERY_INFO)
515
516	#define PDH_BROWSE_DLG_CONFIG_H __MINGW_NAME_AW(PDH_BROWSE_DLG_CONFIG_H)
517	#define PPDH_BROWSE_DLG_CONFIG_H __MINGW_NAME_AW(PPDH_BROWSE_DLG_CONFIG_H)
518
519	#define PdhOpenQuery __MINGW_NAME_AW(PdhOpenQuery)
520	#define PdhAddCounter __MINGW_NAME_AW(PdhAddCounter)
521	#define PdhGetCounterInfo __MINGW_NAME_AW(PdhGetCounterInfo)
522	#define PdhConnectMachine __MINGW_NAME_AW(PdhConnectMachine)
523	#define PdhEnumMachines __MINGW_NAME_AW(PdhEnumMachines)
524	#define PdhEnumObjects __MINGW_NAME_AW(PdhEnumObjects)
525	#define PdhEnumObjectItems __MINGW_NAME_AW(PdhEnumObjectItems)
526	#define PdhMakeCounterPath __MINGW_NAME_AW(PdhMakeCounterPath)
527	#define PdhParseCounterPath __MINGW_NAME_AW(PdhParseCounterPath)
528	#define PdhParseInstanceName __MINGW_NAME_AW(PdhParseInstanceName)
529	#define PdhValidatePath __MINGW_NAME_AW(PdhValidatePath)
530	#define PdhGetDefaultPerfObject __MINGW_NAME_AW(PdhGetDefaultPerfObject)
531	#define PdhGetDefaultPerfCounter __MINGW_NAME_AW(PdhGetDefaultPerfCounter)
532	#define PdhBrowseCounters __MINGW_NAME_AW(PdhBrowseCounters)
533	#define PdhBrowseCountersH __MINGW_NAME_AW(PdhBrowseCountersH)
534	#define PdhExpandCounterPath __MINGW_NAME_AW(PdhExpandCounterPath)
535	#define PdhGetFormattedCounterArray __MINGW_NAME_AW(PdhGetFormattedCounterArray)
536	#define PdhGetRawCounterArray __MINGW_NAME_AW(PdhGetRawCounterArray)
537	#define PdhLookupPerfNameByIndex __MINGW_NAME_AW(PdhLookupPerfNameByIndex)
538	#define PdhLookupPerfIndexByName __MINGW_NAME_AW(PdhLookupPerfIndexByName)
539	#define PdhOpenLog __MINGW_NAME_AW(PdhOpenLog)
540	#define PdhUpdateLog __MINGW_NAME_AW(PdhUpdateLog)
541	#define PdhSelectDataSource __MINGW_NAME_AW(PdhSelectDataSource)
542	#define PdhGetDataSourceTimeRange __MINGW_NAME_AW(PdhGetDataSourceTimeRange)
543	#define PdhLogServiceControl __MINGW_NAME_AW(PdhLogServiceControl)
544	#define PdhLogServiceQuery __MINGW_NAME_AW(PdhLogServiceQuery)
545	#define PdhExpandWildCardPath __MINGW_NAME_AW(PdhExpandWildCardPath)
546	#define PdhBindInputDataSource __MINGW_NAME_AW(PdhBindInputDataSource)
547	#define PdhEnumMachinesH __MINGW_NAME_AW(PdhEnumMachinesH)
548	#define PdhEnumObjectsH __MINGW_NAME_AW(PdhEnumObjectsH)
549	#define PdhEnumObjectItemsH __MINGW_NAME_AW(PdhEnumObjectItemsH)
550	#define PdhExpandWildCardPathH __MINGW_NAME_AW(PdhExpandWildCardPathH)
551	#define PdhGetDefaultPerfObjectH __MINGW_NAME_AW(PdhGetDefaultPerfObjectH)
552	#define PdhGetDefaultPerfCounterH __MINGW_NAME_AW(PdhGetDefaultPerfCounterH)
553	#define PdhEnumLogSetNames __MINGW_NAME_AW(PdhEnumLogSetNames)
554	#define PdhCreateSQLTables __MINGW_NAME_AW(PdhCreateSQLTables)
555	#define PdhVerifySQLDB __MINGW_NAME_AW(PdhVerifySQLDB)
556
557	#if (_WIN32_WINNT >= 0x0600)
558	PDH_STATUS PdhAddEnglishCounterA(
559	  PDH_HQUERY hQuery,
560	  LPCSTR szFullCounterPath,
561	  DWORD_PTR dwUserData,
562	  PDH_HCOUNTER *phCounter
563	);
564
565	PDH_STATUS PdhAddEnglishCounterW(
566	  PDH_HQUERY hQuery,
567	  LPCWSTR szFullCounterPath,
568	  DWORD_PTR dwUserData,
569	  PDH_HCOUNTER *phCounter
570	);
571
572	#define PdhAddEnglishCounter __MINGW_NAME_AW(PdhAddEnglishCounter)
573
574	PDH_STATUS PdhCollectQueryDataWithTime(
575	  PDH_HQUERY hQuery,
576	  LONGLONG *pllTimeStamp
577	);
578
579	PDH_STATUS PdhValidatePathExA(
580	  PDH_HLOG hDataSource,
581	  LPCSTR szFullPathBuffer
582	);
583
584	PDH_STATUS PdhValidatePathExA(
585	  PDH_HLOG hDataSource,
586	  LPCWSTR szFullPathBuffer
587	);
588
589	#define PdhValidatePathEx __MINGW_NAME_AW(PdhValidatePathEx)
590
591	#endif /*(_WIN32_WINNT >= 0x0600)*/
592
593	#ifdef __cplusplus
594	}
595	#endif
596	#endif
