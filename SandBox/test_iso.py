import readline
import rlcompleter
readline.parse_and_bind("tab: complete")

import sys
#sys.path.insert(0,"/git/HyperwallDataBrowse/HCI_Browser")
#import NcImageDataReader as NcR
import vtk
from vtk.util import numpy_support as VN

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


#Get the data
import numpy
import cdms2
f=cdms2.open(sys.prefix+"clt.nc")
s=f("clt",squeeze=1,time=slice(0,1))#,slice(20,22),slice(20,22),squeeze=1)
f=cdms2.open("sampleCurveGrid4.nc")
s=f("sample")#[:-5,5:-5]


#Get mesh information for vtk grid
m=s.getGrid().getMesh()
#For vtk we need to reorder things
m2 = numpy.ascontiguousarray(numpy.transpose(m,(0,2,1)))
m2.resize((m2.shape[0]*m2.shape[1],m2.shape[2]))
m2=m2[...,::-1]
m2b = m2[...,0]+360.
# We need a "level" adding 0 everywhere
# ??? TODO ??? Use actual levels if present (or time? or whatever 3rd dim?)
m3=numpy.concatenate((m2,numpy.zeros((m2.shape[0],1))),axis=1)

# First create the points/vertices (in vcs terms)
deep = False
pts = vtk.vtkPoints()
## Conver tnupmy array to vtk ones
ppV = VN.numpy_to_vtk(m3,deep=False)
pts.SetData(ppV)

ug = vtk.vtkUnstructuredGrid()

## Sets the vertics into the grid
ug.SetPoints(pts)


#Now applies the actual data on each cell
data = VN.numpy_to_vtk(s.filled().flat,deep=True)
#Now construct the cells
for i in range(m.shape[0]):
  lst = vtk.vtkIdList()
  for j in range(4):
    lst.InsertNextId(i*4+j)
  ## ??? TODO ??? when 3D use CUBE?
  ug.InsertNextCell(vtk.VTK_QUAD,lst)

ug.GetCellData().SetScalars(data)

dsw = vtk.vtkDataSetWriter()
dsw.SetFileName("foo.vtk")
dsw.SetInputData(ug)
dsw.Write()
#send me this, and open it up and and inspect in paraview

# Here we try to do a little bit of contouring
#not without values on the points you don't!
c2p = vtk.vtkCellDataToPointData()
c2p.SetInputData(ug)
c2p.Update()

#For contouring duplicate points seem to confuse it
cln = vtk.vtkCleanUnstructuredGrid()
cln.SetInputConnection(c2p.GetOutputPort())

cot = vtk.vtkContourFilter()
#c2p.Update()
#cot.SetInputData(c2p.GetOutput())
#or better still
cot.SetInputConnection(cln.GetOutputPort())
mn,mx = s.min(),s.max()
cot.GenerateValues(10,mn,mx)
# the next two are the same thing, see setter/getter macro definitions in vtkSetGet.h
cot.SetComputeScalars(1)
#cot.ComputeScalarsOn()

#Ok now we have grid and data let's use the mapper
mapper = vtk.vtkDataSetMapper()
mapper.SetInputConnection(cot.GetOutputPort())
# Color range
mapper.SetScalarRange(mn,mx)


# And now we need actors to actually render this thing
act = vtk.vtkActor()
act.SetMapper(mapper)

ren.AddActor(act)

#Now let's have colorbar
## ??? different renderer for this one? so it doesn't zoo in/out
clr = vtk.vtkScalarBarActor()
clr.SetLookupTable(mapper.GetLookupTable())
clr.SetTitle(s.id)
clr.GetPositionCoordinate().SetCoordinateSystemToNormalizedViewport()
clr.GetPositionCoordinate().SetValue(.1,.01)
clr.SetOrientationToHorizontal()
clr.SetWidth(.8)
clr.SetHeight(.1)
ren.AddActor(clr)

# Render the scene and start interaction.
iren.Initialize()
renWin.Render()
iren.Start()

