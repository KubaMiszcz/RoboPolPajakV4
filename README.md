# RoboPolPajakV4
## my engineering thesis - quadrapod

TODO now
popraw te ccr dla serw w init
te funckje ismoving itp dla leg robot itd
sekwencje zrob
jakis timer na bazie systicka ale czestszy



Todo:
stany w swicth na enumach (nie enum class) i prefixy
jakis blink do blinkania
zacznij pisac doku
spowolnienie nogi
balans
sekwencja jednego kroku
nogi do tablicy i metody - umowa kolejnosc: FL FR RR RL
osobna zmienna ze robot wykonuje kroku
enumy w swicthach
doparacuj csy w switchu moveoneLeg
nogi do tablicy albo osobno ale albo to albo to

czy po zmianie na .c wszytsko bedzie ok? nie bedzie tzra pokombinwac dalej z extern itp

co to? bool Name() const{}  w parametrach
co to auto ctor i explicit ctor




przetesuj to extern:
```
someFunction.cpp
void someFunction() {
	int i = 0;
	i = i + 1;
}
``` 
```
main.cpp
#include "Arduino.h"
extern void someFunction();
void setup() {
}
void loop() {
	someFunction();
}
```

##small fixes


##in home
usun zdublowane pliki cuba adc tim tip z myfirmware - to jest tylko do PIO





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

### class Pose
* Vector3d[4]

### class vector3d
* nazwy params in magnityde beginpt endpt

### some infos
* wiertlo na walek 0.9-0.6, to najmnijesze z pudelka, nie 1.4
