[top]
components : unloadque@Unloadqueue
out : readygounload
in: arriveunload unloaddone
Link : arriveunload arriveunload@unloadque
Link : unloaddone unloaddone@unloadque 
Link : readygounload@unloadque readygounload
                  
[unloadque]
preparation : 00:00:10:000  