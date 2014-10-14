import cdms2,vcs

bg=False
bg=True

f=cdms2.open("data_portrait.nc")
s=f("variable_3")
M=f("variable_115")

x=vcs.init()
y=vcs.init()
x.scriptrun("mesh_bug.json")
x.setcolormap("bl_rd_12")
m=x.getmeshfill("portrait")
x.plot(s,M,m,bg=bg)
x.png("mesh_%i" % bg)
y.plot(s,M,m,bg=not bg)
y.png("mesh_%i" % (not bg))

