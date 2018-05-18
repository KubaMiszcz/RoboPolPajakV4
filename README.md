# RoboPolPajakV4
## my engineering thesis - quadrapod

Todo:
* finish it;]

* dorob speed do serva 
#class Servo


### class Leg
* void	MoveToPoint (point3d target)		
* void	RotateAboutVertical(float angle)		obrot S1 wokół mountpt  tylko
* speed paraemter
* przerob movetopoint zeby dzialalo ze speed
* dodaj state

### class Robot
wszytskie pozycje lokalnego UCS robota względem Poczatku trasy!!! bo brak GPS
* void	MoveToPoint (point3d target)
* Point3d	current pos		
* void	MoveToTarget(Point3D target)		
* void	Route(Point3D[ ] route)		trasa punktow
* ??? Speed 
* void	RotateAboutVertical(float angle)		obrot wzglednie o kat
* void	RotateToAngle(float angle)		obrot do kata (bezwzglednie)
* ???? void	SwitchFront()		zmiana frontu robota o 90st CW
* ???? void	SwitchFront(default)		zmiana frontu robota o 90st CW
* void	Settle(Pose)		rozloz robota jak odpowiednio
* enum	Pose: szeroko, standard, wasko		
* float	rotate speed		
* float	move speed		
*	`Pose default front		`

### class enum States
* ismoving
* isindestination
*

### class vector3d
* nazwy params in magnityde beginpt endpt

### some infos
* wiertlo na walek 0.9-0.6, to najmnijesze z pudelka, nie 1.4
