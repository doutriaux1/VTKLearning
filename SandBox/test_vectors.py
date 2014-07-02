import readline
import rlcompleter
import os
readline.parse_and_bind("tab: complete")
from vcs import vcs2vtk
import vcs
import sys
#sys.path.insert(0,"/git/HyperwallDataBrowse/HCI_Browser")
#import NcImageDataReader as NcR
import vtk
from vtk.util import numpy_support as VN


#Get the data
import numpy
import cdms2
import argparse

p = argparse.ArgumentParser()
p.add_argument("-d","--debug",action="store_true",default=False,help="Dumps vtk files for debugging")

pd = p.add_argument_group("data")
#pd.add_argument("-f","--file",default=sys.prefix+"/sample_data/sampleCurveGrid4.nc",help="Input data file name")
pd.add_argument("-f","--file",default=sys.prefix+"/sample_data/clt.nc",help="Input data file name")
pd.add_argument("-v","--var",default="sample",help="variable name in file")
pd.add_argument("-o","--output",default='sample',help="output file(s) name")
pd.add_argument("-t","--output_type",default=["png",],nargs="+",help="file types to dump to",choices=["all","no","png","pdf","ps","svg"])

pV = p.add_argument_group("VTK Representation")
pV.add_argument("-c","--contour",action="store_true",default=False,help="contour plot?")
pV.add_argument("-F","--filled_contours",action="store_true",default=False,help="Filled Contours")
pV.add_argument("-C","--continents",action="store_false",default=True,help="draw continents")
pV.add_argument("-w","--wrap",action="store_true",default=False,help="wrap the data around")
pV.add_argument("-m","--mesh",action="store_true",default=False,help="show mesh")
pV.add_argument("-G","--glyph",action="store_true",default=False,help="show glyph on vertices")

pv = p.add_argument_group("VCS Emulation")
pv.add_argument("-p","--project",default="no",help="Project data")
pv.add_argument("-T","--template",default="default",help="vcs template to use")
pv.add_argument("-g","--graphic_method",metavar="gm",help="graphic method type")
pv.add_argument("-n","--name",help="graphic method name")
pv.add_argument("-b","--bg",default=False,action="store_true",help="Plot in background")

# Create the usual rendering stuff.
renWin = vtk.vtkRenderWindow()
renWin.SetSize(600, 600)
#Renderer
ren = vtk.vtkRenderer()
renWin.AddRenderer(ren)

#Interactor
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)
ren.SetBackground(1, 1, 1) 


p=p.parse_args(sys.argv[1:])

#Interactor
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)
ren.SetBackground(1, 1, 1) 

f=cdms2.open(p.file)
s=data=f("u")
u=numpy.ravel(numpy.ma.masked_greater(data[0],600).filled(0))
v=numpy.ravel(numpy.ma.masked_greater(f("v")[0],600).filled(0))


sh = list(u.shape)
sh.append(1)
u = numpy.reshape(u,sh)
v = numpy.reshape(v,sh)
z = numpy.zeros(u.shape)
w = numpy.concatenate((u,v),axis=1)
w = numpy.concatenate((w,z),axis=1)
print w[0]
print w.shape
print w[:20]
print w.min()
print w.max()
w = VN.numpy_to_vtk(w,deep=True)
w.SetName("vectors")


#norm = numpy.sqrt(u**2+v**2)
#angle = numpy.arctan2(u,v)

if 1:
  #Get mesh information for vtk grid
  m=s.getGrid().getMesh()
  #For vtk we need to reorder things
  m2 = numpy.ascontiguousarray(numpy.transpose(m,(0,2,1)))
  m2.resize((m2.shape[0]*m2.shape[1],m2.shape[2]))
  m2=m2[...,::-1]
  # We need a "level" adding 0 everywhere
  # ??? TODO ??? Use actual levels if present (or time? or whatever 3rd dim?)
  m3=numpy.concatenate((m2,numpy.zeros((m2.shape[0],1))),axis=1)

# First create the points/vertices (in vcs terms)
deep = False
pts = vtk.vtkPoints()
## Conver tnupmy array to vtk ones
ppV = VN.numpy_to_vtk(m3,deep=False)
pts.SetData(ppV)

# Create the VTK grid
# ??? TODO ??? Use StructuredGrid or RectlinearGrid when appropriate
ug = vtk.vtkUnstructuredGrid()

## Ok here we try to apply the geotransform
## And set points onto ug
ug.SetPoints(pts)
ug.GetPointData().AddArray(w)


#Now applies the actual data on each cell
data = VN.numpy_to_vtk(s[0].filled().flat,deep=True)
#print data.GetNumberOfScalarComponents()
#Now construct the cells
for i in range(m.shape[0]):
  lst = vtk.vtkIdList()
  for j in range(4):
    lst.InsertNextId(i*4+j)
  ## ??? TODO ??? when 3D use CUBE?
  ug.InsertNextCell(vtk.VTK_QUAD,lst)

#ug.GetPointData().SetVectors(data)

if p.debug:
  vcs2vtk.dump2VTK(ug)

## Vector attempt
arrow = vtk.vtkArrowSource()
arrow.Update()
glyphFilter = vtk.vtkGlyph2D()
glyphFilter.SetSourceConnection(arrow.GetOutputPort())
glyphFilter.OrientOn()
glyphFilter.SetVectorModeToUseVector()
glyphFilter.SetInputArrayToProcess(1,0,0,0,"vectors")
glyphFilter.SetInputData(ug)


#Data range
mn,mx = s.min(),s.max()

#Ok now we have grid and data let's use the mapper
mapper = vtk.vtkPolyDataMapper()

mapper.SetInputConnection(glyphFilter.GetOutputPort())

if p.debug:
  vcs2vtk.dump2VTK(cot,"cot")

# And now we need actors to actually render this thing
act = vtk.vtkActor()
act.SetMapper(mapper)

ren.AddActor(act)

# Render the scene and start interaction.
iren.Initialize()
renWin.Render()

iren.Start()
