#2 dimentional IK
import math as m

O=[0,0,0]
Z=[0,0,-1] # negative z axis

def dotAngle(a,b,c,d):
	Vectorproduct=(a[0]*b[0])+(a[1]*b[1])+(a[2]*b[2])
	Scalarproduct=(c*d)
	angle=m.degrees(m.acos(Vectorproduct/Scalarproduct))
	return angle

def dotVect(q,w,t,r):
	Scalarproduct=(w*t)
	CosAngle=m.cos(r)
	Vector_i=(Scalarproduct*CosAngle)/q[0]
	Vector_j=(Scalarproduct*CosAngle)/q[1]
	Vector_k=(Scalarproduct*CosAngle)/q[2]
	Vect=[Vector_i,Vector_j,Vector_k]
	return Vect

def mag(e):
	magnitude=m.sqrt(e[0]**2+e[1]**2+e[2]**2)
	return magnitude

magZ=mag(Z)

#initial posture

x1=int(input('x of A : ')) 
y1=int(input('y of A : '))
z1=int(input('z of A : '))

a1=int(input('x of B : '))
b1=int(input('y of B : '))
c1=int(input('z of B : '))

OA=[ x1-O[0] , y1-O[1] , z1-O[2] ] 
AB=[ a1-x1 , b1-y1 , c1-z1 ]
AO=[ -OA[0] ,-OA[1] ,-OA[2] ]
magOA=mag(OA) 	#constant A
magAB=mag(AB)	#constant B
print('\n')

#final posture

x2=int(input("x of A' : "))
y2=int(input("y of A' : "))
z2=int(input("z of A' : "))

a2=int(input("x of B' : "))
b2=int(input("y of B' : "))
c2=int(input("z of B' : "))

oa=[ x2-O[0] , y2-O[1] , z2-O[2] ]
ao=[ -oa[0], -oa[1], -oa[2] ]
abb=[ a2-oa[0] , b2-oa[1] , c2-oa[2] ]
magoa=mag(oa) 	#constant A again
magabb=mag(abb)	#constant B	again
print('\n')

#check the constants

if (magOA!=magoa) or (magAB!=magab):  #OB vector is variable
	print("ERROR IN LENGTH")

#calculation of initial state
else :
	# change in alpha  #SERVO angle

	alpha1=dotAngle(OA,Z,magOA,magZ)
	alpha2=dotAngle(oa,Z,magoa,magZ)
	delAlphaA=alpha2-alpha1

	delAlphaB=dotAngle(OA,oa,magOA,magoa)
	
	if delAlphaA==delAlphaB: 	#check the angle
		print(True)
	else:
		print(False)
	
	# change in gamma  #SERVO angle

	gamma1=dotAngle(AO,AB,magOA,magAB)
	ab=dotVect(ao,magoa,magAB,gamma1)  #get the ab vector #b new position changed because of delAlpha #no change in Gamma yet
	gamma2=dotAngle(ao,abb,magoa,magabb)
	delGammaA=gamma2-gamma1

	delGammaB=dotAngle(ab,abb,magAB,magabb) 

	if delGammaA==delGammaB:	#check the angle
		print(True)
	else:
		print(False)

print(delGammaA,delAlphaA)