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


contour = False
if contour:
  lat = s.getGrid().getLatitude()
  lon = s.getGrid().getLongitude()
  if lat.rank()==1: # rectilinear
    lat = lat[:,numpy.newaxis]*numpy.ones(lon.shape)[numpy.newaxis,:]
    lon = lon[numpy.newaxis,:]*numpy.ones(lat.shape)[:,numpy.newaxis]
  else:
    lat=numpy.ascontiguousarray(lat)
    lon=numpy.ascontiguousarray(lon)
  lat.resize(lat.shape[0]*lat.shape[1],1)
  lon.resize(lat.shape[0]*lat.shape[1],1)
  l = numpy.zeros(lon.shape)
  m3 = numpy.concatenate((lon,lat,l),axis=1)
else:
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
if contour:
  ug = vtk.vtkPolyData()
else:
  ug = vtk.vtkUnstructuredGrid()

## Ok here we try to apply the geotransform
## And set points onto ug
proj = False
if proj:
  geo = vtk.vtkGeoTransform()
  ps = vtk.vtkGeoProjection()
  pd = vtk.vtkGeoProjection()
  pd.SetName('wintri')
  pd.SetCentralMeridian(180)
  geo.SetSourceProjection(ps)
  geo.SetDestinationProjection(pd)
  geopts = vtk.vtkPoints()
  geo.TransformPoints(pts,geopts)
  ## Sets the vertics into the grid
  ug.SetPoints(geopts)
else:
  ## Sets the vertics into the grid
  ug.SetPoints(pts)


#Now applies the actual data on each cell
data = VN.numpy_to_vtk(s.filled().flat,deep=True)
if contour:
  ug.GetPointData().SetScalars(data)
  #polydata need cells too, even if they are all VTK_VERTEX (1 cell : 1 vertex) you need them to do much with it
else:
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


## ??? STILL NOT WORKING 
if contour: 
  cot = vtk.vtkContourFilter()
  #c2p.Update()
  #cot.SetInputData(c2p.GetOutput())
  #or better still
  cot.SetInputConnection(c2p.GetOutputPort())
  cot.GenerateValues(10,0.,1600.)
  # the next two are the same thing, see setter/getter macro definitions in vtkSetGet.h
  cot.SetComputeScalars(1)
  #cot.ComputeScalarsOn()

#Ok now we have grid and data let's use the mapper
mapper = vtk.vtkDataSetMapper()
if contour:
  mapper.SetInputConnection(cot.GetOutputPort())
else:
  print "ok we do come here"
  mapper.SetInputData(ug)
# Color range
mapper.SetScalarRange(0,1600)


# And now we need actors to actually render this thing
act = vtk.vtkActor()
act.SetMapper(mapper)

wrap = True
def doWrap(Mapper,Act):
  act_left = vtk.vtkActor()
  act_left.SetMapper(Mapper)
  act_left.SetProperty(Act.GetProperty())
  T = vtk.vtkTransform()
  T.Translate(-360,0,0)
  act_left.SetUserTransform(T)
  act_right = vtk.vtkActor()
  act_right.SetMapper(Mapper)
  T = vtk.vtkTransform()
  T.Translate(360,0,0)
  act_right.SetUserTransform(T)
  act_right.SetProperty(Act.GetProperty())
  A = vtk.vtkAssembly()
  A.AddPart(act_left)
  A.AddPart(Act)
  A.AddPart(act_right)
  return A

if wrap:
  A = doWrap(mapper,act)
  ren.AddActor(A)
else:
  ren.AddActor(act)

#This bits show the mesh, needs a second mapper
mesh = False
if mesh:
  mapper2 = vtk.vtkDataSetMapper()
  mapper2.SetInputData(ug)
  act2 = vtk.vtkActor()
  act2.SetMapper(mapper2)
  act2.GetProperty().SetRepresentationToWireframe()
  if wrap:
    A2 = doWrap(mapper2,act2)
    ren.AddActor(A2)
  else:
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

## Trying the glyph thing to see the points
glyph = False
if glyph:
  S=vtk.vtkSphereSource()
  if proj:
    sc = max(geopts.GetBounds())/90.
    S.SetRadius(sc)
  else:
    S.SetRadius(1)
  g = vtk.vtkGlyph3D()
  g.SetInputData(ug)
  g.SetSourceConnection(S.GetOutputPort())
  gmap = vtk.vtkPolyDataMapper()
  gmap.SetInputConnection(g.GetOutputPort())
  gact = vtk.vtkActor()
  gact.SetMapper(gmap)
  ren.AddActor(gact)

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

