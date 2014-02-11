import vcs
import vtk

## This module contains some convenience function from vcs2vtk



## Continents first
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
          pts.InsertNextPoint(L,l,0.0001)
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


#Geo projection
def project(pts,projName='wintri',meridian=None):
  geo = vtk.vtkGeoTransform()
  ps = vtk.vtkGeoProjection()
  pd = vtk.vtkGeoProjection()
  pd.SetName(projName)
  if meridian is not None:
    pd.SetCentralMeridian(180)
  geo.SetSourceProjection(ps)
  geo.SetDestinationProjection(pd)
  geopts = vtk.vtkPoints()
  geo.TransformPoints(pts,geopts)
  return geopts
