i=57
def aMarker(i):
  f=open("marker%.2i.txt" % i)
  coords = None
  dic={"line":[],"poly":[]}
  for l in f.xreadlines():
    if l.strip() in ["line","poly"]: # new set of coords
      if coords is None:
        coords =[[],[]]
      else:
        dic[type].append(coords)
      type = l.strip()
    else:
      sp=l.strip().split(",")
      coords[0].append(float(sp[0]))
      coords[1].append(float(sp[1]))

  try:
    dic[type].append(coords)
    return dic
  except:
    return
import json

markers = {}
for i in range(203):
  nm = "w%.2i" % i
  m = aMarker(i)
  if m is not None:
    markers[nm]=m

f = open("wmo_symbols.json","w")
print markers["w01"]["line"][0]
json.dump(markers,f,sort_keys=True)
f.close()
