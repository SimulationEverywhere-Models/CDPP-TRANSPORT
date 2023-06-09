[top]
components : unloadque@Unloadqueue unloadser@Unloadserver 
in :   arriveunload
out : exitunload
Link : arriveunload arriveunload@unloadque
Link : readygounload@unloadque enterunload@unloadser
Link : readyreceive@unloadser unloaddone@unloadque
Link : exitunload@unloadser exitunload

[unloadque]
preparation : 00:00:10:000 

[unloadser]
distribution : normal
mean : 180
deviation : 0 

