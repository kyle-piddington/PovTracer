// cs174, assignment 1 sample file (RIGHT HANDED)

camera {
  location  <0, 0, -4>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}

light_source {<1, 1, -4.5> color rgb <1.0, 1.0, 1.0>}

box { <-8,-8,-8>, <8,8,8>
  pigment { color rgb <0.7, 0.4, 0.4>}
  finish {ambient 0.2 diffuse 0.4 }
}

box { <-0.5,-0.5,-0.5>, <0.5,0.5,0.5> 
  pigment { color rgb <0.2, 0.2, 0.8>}
  finish {ambient 0.2 diffuse 1.0 }
}




