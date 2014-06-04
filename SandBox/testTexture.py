import vtk

png = vtk.vtkPNGReader()
png.SetFileName("/git/uvcdat/Packages/vcs/Share/uvcdat_texture.png")
T=vtk.vtkTexture()
T.SetInputConnection(png.GetOutputPort())
p=vtk.vtkPlaneSource()
p.SetCenter(0,0,0)
p.SetNormal(0,0,1)

tmp = vtk.vtkTextureMapToPlane()
tmp.SetInputConnection(p.GetOutputPort())

pm = vtk.vtkPolyDataMapper()
pm.SetInputConnection(tmp.GetOutputPort())

ta = vtk.vtkActor()
ta.SetMapper(pm)
ta.SetTexture(T)

r = vtk.vtkRenderer()
r.AddActor(ta)

rw = vtk.vtkRenderWindow()
rw.AddRenderer(r)

rw.Render()

raw_input("PressENTER")

