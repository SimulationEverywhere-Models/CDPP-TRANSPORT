[top]
components : loadque@Loadqueue
out : readygoload
in:  arriveload loaddone
Link : arriveload arriveload@loadque
Link : loaddone loaddone@loadque 
Link : readygoload@loadque readygoload

[loadque]
preparation : 00:00:10:000  


