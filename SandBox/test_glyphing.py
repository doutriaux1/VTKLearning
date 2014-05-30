# vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4

import vtk
import numpy
from vcs.vcs2vtk import genPoly

# Tests on hurrican glyph

w = vtk.vtkRenderWindow()
ren = vtk.vtkRenderer()

w.AddRenderer(ren)

ren.SetBackground(100,100,100)

g = vtk.vtkGlyph2D()

markers = vtk.vtkPolyData()

xs = [0,.5,1.]
ys = [0.,1.,.5]
N = len(xs)

pts = vtk.vtkPoints()
for i in range(N):
  pts.InsertNextPoint(xs[i],ys[i],0)
pts.SetNumberOfPoints(N)

markers.SetPoints(pts)

t="hurricane"

s =0.1

ds = vtk.vtkDiskSource()
ds.SetInnerRadius(.58*s)
ds.SetOuterRadius(s)
gf = vtk.vtkGeometryFilter()
gf.SetInputConnection(ds.GetOutputPort())
gf.Update()
pd1 = gf.GetOutput()
print pd1
raw_input()
sys.exit()
apd = vtk.vtkAppendPolyData()
apd.AddInputData(gf.GetOutput())

pts = vtk.vtkPoints()
pd = vtk.vtkPolyData()
polygons = vtk.vtkCellArray()
add_angle = numpy.pi/360.
coords = []
angle1 = .6*numpy.pi
angle2 = .88*numpy.pi
while angle1<=angle2:
  coords.append([s*2+2*s*numpy.cos(angle1),2*s*numpy.sin(angle1)])
  angle1+=add_angle
angle1=.79*numpy.pi
angle2=.6*numpy.pi
while angle1>=angle2:
  coords.append([s*2.25+s*4*numpy.cos(angle1),-s*2+s*4*numpy.sin(angle1)])
  angle1-=add_angle
poly = genPoly(coords,pts,filled=True)
polygons.InsertNextCell(poly)
coords=[]
angle1 = 1.6*numpy.pi
angle2 = 1.9*numpy.pi
while angle1 <= angle2:
  coords.append( [- s*2 + s*2*numpy.cos(angle1),s*2*numpy.sin(angle1)])
  angle1 += add_angle
angle1 = 1.8*numpy.pi
angle2 = 1.6*numpy.pi
while angle1 >= angle2:
  coords.append( [- s*2.27 + s*4*numpy.cos(angle1), s*2 + s*4*numpy.sin(angle1)])
  angle1 -= add_angle
poly = genPoly(coords,pts,filled=True)
polygons.InsertNextCell(poly)
pd.SetPoints(pts)
pd.SetPolys(polygons)
apd.AddInputData(pd)
apd.Update()
g.SetSourceData(apd.GetOutput())
g.SetInputData(markers)
a=vtk.vtkActor()
m=vtk.vtkPolyDataMapper()
m.SetInputConnection(g.GetOutputPort())
m.Update()
a.SetMapper(m)
p=a.GetProperty()
p.SetColor(100.,0,0)
ren.AddActor(a)
w.Render()
raw_input("Done")


