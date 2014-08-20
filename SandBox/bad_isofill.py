import vtk,cdms2,numpy

from vtk.util import numpy_support as VN

f=cdms2.open("celine.nc")
data=f("data")
ug = vtk.vtkStructuredGrid()
lat = data.getLatitude()
lon = data.getLongitude()
lat = lat[:,numpy.newaxis]*numpy.ones(lon.shape)[numpy.newaxis,:]
lon = lon[numpy.newaxis,:]*numpy.ones(lat.shape)[:,numpy.newaxis]
ug.SetDimensions(lat.shape[1],lat.shape[0],1)
lon = numpy.ma.ravel(lon)
lat = numpy.ma.ravel(lat)
sh = list(lat.shape)
sh.append(1)
lon = numpy.ma.reshape(lon,sh)
lat = numpy.ma.reshape(lat,sh)
z = numpy.zeros(lon.shape)
m3 = numpy.concatenate((lon,lat),axis=1)
m3 = numpy.concatenate((m3,z),axis=1)
xm=lon.min()
xM=lon.max()
ym=lat.min()
yM=lat.max()
# First create the points/vertices (in vcs terms)
deep = True
pts = vtk.vtkPoints()
## Convert nupmy array to vtk ones
ppV = VN.numpy_to_vtk(m3,deep=deep)
pts.SetData(ppV)
ug.SetPoints(pts)
data = VN.numpy_to_vtk(data.filled(0.).flat,deep=True)
ug.GetPointData().SetScalars(data)

sFilter = vtk.vtkDataSetSurfaceFilter()
sFilter.SetInputData(ug)
sFilter.Update()
l = [-4.0584776401519775, -2, -1.5, -1.0, -0.4, -0.1, 0, 0.1, 0.4, 1.0, 1.5, 2, 7.875967502593994]
cols = [[0, 57, 100],[0, 100, 33],[27, 100, 0],[88, 100, 0], [100, 78, 0], [100, 100, 100], [100, 100, 100], [100, 32, 0], [100, 17, 0], [75, 0, 0], [45, 0, 0], [49, 0, 24],]

mapper = vtk.vtkPolyDataMapper()
cot = vtk.vtkBandedPolyDataContourFilter()
cot.ClippingOn()
cot.SetInputData(sFilter.GetOutput())
cot.SetNumberOfContours(len(l))
for j,v in enumerate(l):
      cot.SetValue(j,l[j])
#cot.SetScalarModeToIndex()
cot.Update()

mapper.SetInputConnection(cot.GetOutputPort())
lut = vtk.vtkLookupTable()
lut.SetNumberOfTableValues(len(cols))
for j,color in enumerate(cols):
    r,g,b = cols[j]
    lut.SetTableValue(j,r/100.,g/100.,b/100.)
mapper.SetLookupTable(lut)
mapper.SetScalarRange(0, len(l) - 1)
mapper.SetScalarModeToUseCellData()

act = vtk.vtkActor()
act.SetMapper(mapper)

ren=vtk.vtkRenderer()
ren.AddActor(act)
renWin=vtk.vtkRenderWindow()
renWin.SetSize(800,600)
renWin.AddRenderer(ren)
renWin.Render()

raw_input("ok press enter now")
