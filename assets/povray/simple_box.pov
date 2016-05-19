// cs174, assignment 1 sample file (RIGHT HANDED)

camera {
  location  <0, 10.5, -18>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}

light_source {<-10, 10, 10> color rgb <1.0, 0.0, 0.0>}
light_source {<-10, 10, -10> color rgb <0.0, 1.0, 0.0>}
light_source {<10, 10, -10> color rgb <1.0, 1.0, 0.0>}
light_source {<10, 10, 10> color rgb <0.0, 0.0, 1.0>}

plane {<0, 1, 0>, 0
  pigment {color rgb <0.2, 0.2, 0.2>}
  finish {ambient 0.4 diffuse 4.0 reflection 0.4}
}
plane {<0, -1, 0>, -12
  pigment {color rgb <1, 1, 1>}
  finish {ambient 0.4 diffuse 4.0 reflection 0.4}
}




sphere {<0,0,0>, 4
   pigment {color rgb <1.0,1.0,1.0> }
   finish {ambient 0.3 specular 0.8 reflection 0.3 ior 1.33}
}

sphere {<0,4,0>,0.5
   pigment {color rgb <1.0,1.0,1.0> }
   finish {ambient 0.3 specular 0.8 reflection 0.8 refraction 1 ior 1.08}
   translate <0, 0, -7>
   rotate <0, 0, 0>
}
sphere {<0,4,0>,0.5
   pigment {color rgb <1.0,1.0,1.0> }
   finish {ambient 0.3 specular 0.8 reflection 0.8 refraction 1 ior 1.08}
   translate <0, 0, -7>
   rotate <0, 30, 0>
}
sphere {<0,4,0>,0.5
   pigment {color rgb <1.0,1.0,1.0> }
   finish {ambient 0.3 specular 0.8 reflection 0.8 refraction 1 ior 1.08}
   translate <0, 0, -7>
   rotate <0, 60, 0>
}
sphere {<0,4,0>,0.5
   pigment {color rgb <1.0,1.0,1.0> }
   finish {ambient 0.3 specular 0.8 reflection 0.8 refraction 1 ior 1.08}
   translate <0, 0, -7>
   rotate <0, 90, 0>
}
sphere {<0,4,0>,0.5
   pigment {color rgb <1.0,1.0,1.0> }
   finish {ambient 0.3 specular 0.8 reflection 0.8 refraction 1 ior 1.08}
   translate <0, 0, -7>
   rotate <0,120, 0>
}
sphere {<0,4,0>,0.5
   pigment {color rgb <1.0,1.0,1.0> }
   finish {ambient 0.3 specular 0.8 reflection 0.8 refraction 1 ior 1.08}
   translate <0, 0, -7>
   rotate <0,150, 0>
}
sphere {<0,4,0>,0.5
   pigment {color rgb <1.0,1.0,1.0> }
   finish {ambient 0.3 specular 0.8 reflection 0.8 refraction 1 ior 1.08}
   translate <0, 0, -7>
   rotate <0,180, 0>
}
sphere {<0,4,0>,0.5
   pigment {color rgb <1.0,1.0,1.0> }
   finish {ambient 0.3 specular 0.8 reflection 0.8 refraction 1 ior 1.08}
   translate <0, 0, -7>
   rotate <0, 210, 0>
}
sphere {<0,4,0>,0.5
   pigment {color rgb <1.0,1.0,1.0> }
   finish {ambient 0.3 specular 0.8 reflection 0.8 refraction 1 ior 1.08}
   translate <0, 0, -7>
   rotate <0, 240, 0>
}
sphere {<0,4,0>,0.5
   pigment {color rgb <1.0,1.0,1.0> }
   finish {ambient 0.3 specular 0.8 reflection 0.8 refraction 1 ior 1.08}
   translate <0, 0, -7>
   rotate <0, 270, 0>
}
sphere {<0,4,0>,0.5
   pigment {color rgb <1.0,1.0,1.0> }
   finish {ambient 0.3 specular 0.8 reflection 0.8 refraction 1 ior 1.08}
   translate <0, 0, -7>
   rotate <0, 300, 0>
}
sphere {<0,4,0>,0.5
   pigment {color rgb <1.0,1.0,1.0> }
   finish {ambient 0.3 specular 0.8 reflection 0.8 refraction 1 ior 1.08}
   translate <0, 0, -7>
   rotate <0, 330, 0>
}


box { <-1.5,0,-0.5>, <-0.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 0, 0>
  

}

box { <0.5,0,-0.5>, <1.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 0, 0>
  

}

box { <-1.5,3,-0.5>, <1.5,4,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 0, 0>
  
}

box { <-1.5,0,-0.5>, <-0.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 30, 0>
  

}

box { <0.5,0,-0.5>, <1.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 30, 0>
  

}

box { <-1.5,3,-0.5>, <1.5,4,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 30, 0>
  
}

box { <-1.5,0,-0.5>, <-0.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 60, 0>
  

}

box { <0.5,0,-0.5>, <1.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 60, 0>
  

}

box { <-1.5,3,-0.5>, <1.5,4,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 60, 0>
  
}

box { <-1.5,0,-0.5>, <-0.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 60, 0>
  

}

box { <0.5,0,-0.5>, <1.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 90, 0>
  

}

box { <-1.5,3,-0.5>, <1.5,4,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 90, 0>
  
}

box { <-1.5,0,-0.5>, <-0.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 90, 0>
  

}

box { <0.5,0,-0.5>, <1.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 90, 0>
  

}

box { <-1.5,3,-0.5>, <1.5,4,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 120, 0>
  
}

box { <-1.5,0,-0.5>, <-0.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 120, 0>
  

}

box { <0.5,0,-0.5>, <1.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 120, 0>
  

}

box { <-1.5,3,-0.5>, <1.5,4,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 150, 0>
  
}

box { <-1.5,0,-0.5>, <-0.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 150, 0>
  

}

box { <0.5,0,-0.5>, <1.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 150, 0>
  

}

box { <-1.5,3,-0.5>, <1.5,4,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 150, 0>
  
}

box { <-1.5,0,-0.5>, <-0.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 180, 0>
  

}

box { <0.5,0,-0.5>, <1.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 180, 0>
  

}

box { <-1.5,3,-0.5>, <1.5,4,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 180, 0>
  
}

box { <-1.5,0,-0.5>, <-0.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 180, 0>
  

}

box { <0.5,0,-0.5>, <1.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 210, 0>
  

}

box { <-1.5,3,-0.5>, <1.5,4,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 210, 0>
  
}

box { <-1.5,0,-0.5>, <-0.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 210, 0>
  

}

box { <0.5,0,-0.5>, <1.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 210, 0>
  

}

box { <-1.5,3,-0.5>, <1.5,4,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 240, 0>
  
}

box { <-1.5,0,-0.5>, <-0.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 240, 0>
  

}

box { <0.5,0,-0.5>, <1.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 240, 0>
  

}

box { <-1.5,3,-0.5>, <1.5,4,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 240, 0>
  
}

box { <-1.5,0,-0.5>, <-0.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 270, 0>
  

}

box { <0.5,0,-0.5>, <1.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 270, 0>
  

}

box { <-1.5,3,-0.5>, <1.5,4,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 270, 0>
  
}

box { <-1.5,0,-0.5>, <-0.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 300, 0>
  

}

box { <0.5,0,-0.5>, <1.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 300, 0>
  

}

box { <-1.5,3,-0.5>, <1.5,4,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 300, 0>
  
}

box { <-1.5,0,-0.5>, <-0.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 330, 0>
  

}

box { <0.5,0,-0.5>, <1.5,3,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 330, 0>
  

}

box { <-1.5,3,-0.5>, <1.5,4,0.5> 
  pigment { color rgb <0.4, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
  translate <0, 0, -7>
  rotate <0, 330, 0>
  
}




