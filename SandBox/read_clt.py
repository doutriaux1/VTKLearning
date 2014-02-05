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
# Create the VTK grid
# ??? TODO ??? Use StructuredGrid or RectlinearGrid when appropriate
ug = vtk.vtkUnstructuredGrid()

# First create the points/vertices (in vcs terms)
deep = False
pts = vtk.vtkPoints()
## Conver tnupmy array to vtk ones
ppV = VN.numpy_to_vtk(m3,deep=False)
pts.SetData(ppV)

## Sets the vertics into the grid
ug.SetPoints(pts)

#Now construct the cells
for i in range(m.shape[0]):
  lst = vtk.vtkIdList()
  for j in range(4):
    lst.InsertNextId(i*4+j)
  ## ??? TODO ??? when 3D use CUBE?
  ug.InsertNextCell(vtk.VTK_QUAD,lst)

#Now applies the actual data on each cell
data = VN.numpy_to_vtk(s.filled().flat,deep=True)
ug.GetCellData().SetScalars(data)


# Her we try to do a little bit of contouring
## ??? STILL NOT WORKING 
##  cot = vtk.vtkContourFilter()
##  cot.SetInputData(ug)
##  cot.GenerateValues(10,0.,1600.)


#Ok now we have grid and data let's use the mapper
mapper = vtk.vtkDataSetMapper()
mapper.SetInputData(ug)
# Color range
mapper.SetScalarRange(0,1600)


# And now we need actors to actually render this thing
act = vtk.vtkActor()
act.SetMapper(mapper)
ren.AddActor(act)

#This bits show the mesh, needs a second mapper
if mesh:
  mapper2 = vtk.vtkDataSetMapper()
  mapper2.SetInputData(ug)
  act2 = vtk.vtkActor()
  act2.SetMapper(mapper2)
  act2.GetProperty().SetRepresentationToWireframe()
  ren.AddActor(act2)

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


# The following saves plo to disk
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

