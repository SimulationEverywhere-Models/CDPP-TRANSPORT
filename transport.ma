[top]
components : gen@Gen load unload
out : exitunload
Link : go@gen arriveload@load
Link : exitload@load arriveunload@unload
Link : exitunload@unload exitunload

[load]
components : loadque@Loadqueue loadser@Loadserver 
out : exitload
in: arriveload
Link : arriveload arriveload@loadque
Link : readygoload@loadque enterload@loadser
Link : readyaccept@loadser loaddone@loadque
Link : exitload@loadser exitload

[unload]
components : unloadque@Unloadqueue unloadser@Unloadserver 
out : exitunload
in: arriveunload
Link : arriveunload arriveunload@unloadque
Link : readygounload@unloadque enterunload@unloadser
Link : readyreceive@unloadser unloaddone@unloadque
Link : exitunload@unloadser exitunload

[gen]
distribution : normal
mean : 60
deviation : 0 

[loadser]
distribution : normal
mean : 180
deviation : 0 

[loadque]
preparation : 00:00:10:000 

[unloadser]
distribution : normal
mean : 150
deviation : 0 

[unloadque]
preparation : 00:00:10:000 

