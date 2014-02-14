import readline
import rlcompleter
import os
readline.parse_and_bind("tab: complete")
import vcs2vtk
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
pd.add_argument("-f","--file",default=sys.prefix+"/sample_data/sampleCurveGrid4.nc",help="Input data file name")
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

if "all" in p.output_type:
  p.output_type = ["png","pdf","ps","svg"]
f=cdms2.open(p.file)
s=f(p.var)

if p.continents:
  #Continents
  contData = vcs2vtk.continentsVCS2VTK(os.environ["HOME"]+"/.uvcdat/data_continent_political")
  contMapper = vtk.vtkPolyDataMapper()
  contMapper.SetInputData(contData)
  contActor = vtk.vtkActor()
  contActor.SetMapper(contMapper)
  contActor.GetProperty().SetColor(0.,0.,0.)
  if p.wrap:
    A0 = vcs2vtk.doWrap(contMapper,contActor)


if 0:
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
if 0:
  ug = vtk.vtkPolyData()
else:
  ug = vtk.vtkUnstructuredGrid()

## Ok here we try to apply the geotransform
## And set points onto ug
if p.project!="no":
  geopts = vcs2vtk.project(pts,p.project)
  ## Sets the vertics into the grid
  ug.SetPoints(geopts)
  if p.continents:
    cpts = contData.GetPoints()
    gcpts = vcs2vtk.project(cpts)
    contData.SetPoints(gcpts)
else:
  ## Sets the vertics into the grid
  ug.SetPoints(pts)


#Now applies the actual data on each cell
data = VN.numpy_to_vtk(s.filled().flat,deep=True)
if 0:
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

if p.debug:
  vcs2vtk.dump2VTK(ug)


#Data range
mn,mx = s.min(),s.max()

#Ok now we have grid and data let's use the mapper
mapper = vtk.vtkDataSetMapper()

if p.contour: 
  # Sets data to point instead of just cells
  c2p = vtk.vtkCellDataToPointData()
  c2p.SetInputData(ug)
  c2p.Update()
  if p.debug:
    vcs2vtk.dump2VTK(c2p)
  #For contouring duplicate points seem to confuse it
  cln = vtk.vtkCleanUnstructuredGrid()
  cln.SetInputConnection(c2p.GetOutputPort())
  if p.debug:
    vcs2vtk.dump2VTK(cln)
  #Now this filter seens to create the good polydata
  sFilter = vtk.vtkDataSetSurfaceFilter()
  sFilter.SetInputConnection(cln.GetOutputPort())
  sFilter.Update()
  if p.debug:
    vcs2vtk.dump2VTK(sFilter)
  if p.filled_contours:
    cot = vtk.vtkBandedPolyDataContourFilter()
  else:
    cot = vtk.vtkContourFilter()
  cot.SetInputData(sFilter.GetOutput())
  if p.debug:
    vcs2vtk.dump2VTK(cot)

  # Here we generate the levels and the colormap to go with it
  Nlevs = 10
  cot.SetNumberOfContours(Nlevs+1)
  #At that point let's try to tweak color table
  lut = vtk.vtkLookupTable()
  lut.SetNumberOfTableValues(Nlevs)
  #lut.SetTableRange(0,Nlevs)
  levs=vcs.mkevenlevels(mn,mx,Nlevs)
  cols=vcs.getcolors(levs)
  x=vcs.init()
  cmap=x.getcolormap("rainbow")

  for i in range(Nlevs):
    cot.SetValue(i,levs[i])
    r,g,b = cmap.index[cols[i]]
    print i,cols[i],r,g,b
    lut.SetTableValue(i,r/100.,g/100.,b/100.)
  cot.SetValue(Nlevs,levs[-1])

  cot.Update()

  mapper.SetInputConnection(cot.GetOutputPort())
  mapper.SetLookupTable(lut)
else:
  mapper.SetInputData(ug)

mapper.SetScalarRange(mn,mx)
if p.debug:
  vcs2vtk.dump2VTK(cot,"cot")

# And now we need actors to actually render this thing
act = vtk.vtkActor()
act.SetMapper(mapper)

if p.wrap:
  A = vcs2vtk.doWrap(mapper,act)
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
  if p.wrap:
    A2 = vcs2vtk.doWrap(mapper2,act2)
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
  if p.project:
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
  if p.wrap:
    A3 = vcs2vtk.doWrap(gmap,gact)
    ren.AddActor(A3)
  else:
    ren.AddActor(gact)
#continetns last to be on top?
if p.continents:
  if p.wrap:
    ren.AddActor(A0)
  else:
    ren.AddActor(contActor)
# Render the scene and start interaction.
iren.Initialize()
renWin.Render()


# The following saves plo to disk
if not "no" in p.output_type:
  # Dump to ps/pdf/svg
  gl  = vtk.vtkGL2PSExporter()
  gl.SetInput(renWin)
  gl.SetCompress(0) # Do not compress
  gl.SetFilePrefix(p.output)
  if "svg" in p.output_type:
    gl.SetFileFormatToSVG()
    gl.Write()
  if "ps" in p.output_type:
    gl.SetFileFormatToPS()
    gl.Write()
  if "pdf" in p.output_type:
    gl.SetFileFormatToPDF()
    gl.Write()

  # Dumps to png
  if "png" in p.output_type:
    try:
      os.remove(p.output+".png")
    except:
      pass
    imgfiltr = vtk.vtkWindowToImageFilter()
    imgfiltr.SetInput(renWin)
    imgfiltr.SetMagnification(3)
    imgfiltr.SetInputBufferTypeToRGBA()
    imgfiltr.Update()
    writer = vtk.vtkPNGWriter()
    writer.SetInputConnection(imgfiltr.GetOutputPort())
    writer.SetFileName(p.output+".png")
    writer.Write()
  renWin.Render()

iren.Start()
