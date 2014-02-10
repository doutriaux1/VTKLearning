import readline
import rlcompleter
import os
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
#f=cdms2.open(sys.prefix+"/sample_data/clt.nc")
#s=f("clt",squeeze=1,time=slice(0,1))#,slice(20,22),slice(20,22),squeeze=1)
f=cdms2.open(sys.prefix+"/sample_data/sampleCurveGrid4.nc")
s=f("sample")#[:-5,5:-5]

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

#Ok now we have grid and data let's use the mapper
mapper = vtk.vtkDataSetMapper()
mapper.SetInputData(ug)

# Color range
mapper.SetScalarRange(0,1600)

#Continetns go here
def continentsVCS2VTK(fnm):
  """ This converts vcs continents files to vtkpolydata
  Author: Charles Doutriaux
  Input: vcs continent file name
  """
  poly =vtk.vtkPolyData()
  cells = vtk.vtkCellArray()
  pts = vtk.vtkPoints()
  f=open(fnm)
  ln=f.readline()
  while ln.strip().split()!=["-99","-99"]:
    # Many lines, need to know number of points
    N = int(ln.split()[0])
    # Now create and store these points
    n=0
    npts = pts.GetNumberOfPoints()
    while n<N:
        ln=f.readline()
        while len(ln)>2:
          l,L=float(ln[:8]),float(ln[8:16])
          pts.InsertNextPoint(L,l,0)
          ln=ln[16:]
          n+=2
    ln = vtk.vtkPolyLine()
    ln.GetPointIds().SetNumberOfIds(N/2)
    for i in range(N/2): ln.GetPointIds().SetId(i,i+npts)
    cells.InsertNextCell(ln)
    ln=f.readline()
  poly.SetPoints(pts)
  poly.SetLines(cells)
  return poly

contData = continentsVCS2VTK(os.environ["HOME"]+"/.uvcdat/data_continent_political")

dsw = vtk.vtkDataSetWriter()
dsw.SetFileName("foo.vtk")
dsw.SetInputData(ug)
dsw.Write()

contMapper = vtk.vtkPolyDataMapper()
contMapper.SetInputData(contData)
contActor = vtk.vtkActor()
contActor.SetMapper(contMapper)
ren.AddActor(contActor)

# And now we need actors to actually render this thing
act = vtk.vtkActor()
act.SetMapper(mapper)
ren.AddActor(act)

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


# The following saves plo to disk
dump = False
if dump:
  # Dump to ps/pdf/svg
  gl  = vtk.vtkGL2PSExporter()
  gl.SetInput(renWin)
  gl.SetCompress(0) # Do not compress
  gl.SetFilePrefix("sample")
  gl.SetFileFormatToSVG()
  gl.Write()
  gl.SetFileFormatToPS()
  gl.Write()
  gl.SetFileFormatToPDF()
  gl.Write()

  # Dumps to png
  imgfiltr = vtk.vtkWindowToImageFilter()
  imgfiltr.SetInput(renWin)
  imgfiltr.SetMagnification(3)
  imgfiltr.SetInputBufferTypeToRGBA()
  imgfiltr.Update()
  writer = vtk.vtkPNGWriter()
  writer.SetInputConnection(imgfiltr.GetOutputPort())
  writer.SetFileName("sample.png")
  writer.Write()

