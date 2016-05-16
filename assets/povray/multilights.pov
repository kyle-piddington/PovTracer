
camera {
  location  <0, 0, 14>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}

light_source {<-10, 10, 10> color rgb <1.0, 0.0, 0.0>}
light_source {<-10, 10, -10> color rgb <0.0, 1.0, 0.0>}
light_source {<10, 10, -10> color rgb <1.0, 1.0, 0.0>}
light_source {<10, 10, 10> color rgb <0.0, 0.0, 1.0>}

sphere { <0, 0, 0>, 2
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.4 roughness 0.001}
  translate <0, 0, 0>
}

plane {<0, 1, 0>, -4
  pigment {color rgb <0.2, 0.2, 0.2>}
  finish {ambient 0.4 diffuse 4.0 reflection 0.8}
}
