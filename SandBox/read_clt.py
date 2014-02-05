import readline
import rlcompleter
readline.parse_and_bind("tab: complete")

import sys
#sys.path.insert(0,"/git/HyperwallDataBrowse/HCI_Browser")
#import NcImageDataReader as NcR
import vtk
from vtk.util import numpy_support as VN

import numpy

import cdms2

#f=cdms2.open(sys.prefix+"/sample_data/clt.nc")
#s=f("clt",squeeze=1,time=slice(0,1))#,slice(20,22),slice(20,22),squeeze=1)
f=cdms2.open(sys.prefix+"/sample_data/sampleCurveGrid4.nc")
s=f("sample")#[:-5,5:-5]
print s.shape

m=s.getGrid().getMesh()
print m.shape

m2 = numpy.ascontiguousarray(numpy.transpose(m,(0,2,1)))
m2.resize((m2.shape[0]*m2.shape[1],m2.shape[2]))
m2=m2[...,::-1]
print m2.shape
m3=numpy.concatenate((m2,numpy.zeros((m2.shape[0],1))),axis=1)
ug = vtk.vtkUnstructuredGrid()
pts = vtk.vtkPoints()
ppV = VN.numpy_to_vtk(m3,deep=True)
data = VN.numpy_to_vtk(s.filled().flat,deep=True)
indices=numpy.arange(m2.shape[0],dtype=numpy.int64)
pts.SetData(ppV)
ug.SetPoints(pts)

for i in range(m.shape[0]):
  lst = vtk.vtkIdList()
  for j in range(4):
    lst.InsertNextId(i*4+j)

  ug.InsertNextCell(vtk.VTK_QUAD,lst)

ug.GetCellData().SetScalars(data)
mapper = vtk.vtkDataSetMapper()
mapper.SetInputData(ug)
mapper.SetScalarRange(0,1600)
act = vtk.vtkActor()
act.VisibilityOn()
act.SetMapper(mapper)

mapper2 = vtk.vtkDataSetMapper()
mapper2.SetInputData(ug)
act2 = vtk.vtkActor()
act2.SetMapper(mapper2)
act2.GetProperty().SetRepresentationToWireframe()

print ug.GetCellData().GetArray(0).GetRange()
# Create the usual rendering stuff.
ren = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)
renWin.SetSize(300, 300)
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)

ren.SetBackground(1, 1, 1) 

ren.AddActor(act)
ren.AddActor(act2)

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

