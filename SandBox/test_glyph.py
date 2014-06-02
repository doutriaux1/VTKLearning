import readline
import rlcompleter
readline.parse_and_bind("tab: complete")
import vtk
import vcs2vtk

renWin = vtk.vtkRenderWindow()
ren = vtk.vtkRenderer()
renWin.AddRenderer(ren)

## glyph
g=vtk.vtkGlyph2D()

##Glytph Source

##Locations
pts = vtk.vtkPoints()
pts.InsertNextPoint(0,0,0)
pts.InsertNextPoint(5,0,0)
pts.InsertNextPoint(10,0,0)
pd = vtk.vtkPolyData()
pd.SetPoints(pts)
g.SetInputData(pd)


##Glyph Source (triangle here)
psrc = vtk.vtkPoints()
psrc.InsertNextPoint(0,0,0)
psrc.InsertNextPoint(1,0,0)
psrc.InsertNextPoint(0.5,1,0)
psrc.InsertNextPoint(0,0,0)
pd2 = vtk.vtkPolyData()
pd2.SetPoints(psrc)
psrc = vtk.vtkGlyphSource2D()
psrc.SetScale(1.)
psrc.SetColor(1.,0.,0.)
psrc.SetGlyphTypeToCircle()

g.SetSourceConnection(psrc.GetOutputPort())

m = vtk.vtkPolyDataMapper()
m.SetInputConnection(g.GetOutputPort())
m.Update()

ga = vtk.vtkActor()
ga.SetMapper(m)

ren.AddActor(ga)
ren.SetBackground(.2,.3,.4)
renWin.AddRenderer(ren)
renWin.Render()
raw_input("Press Enter")


