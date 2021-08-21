from database import TurbojetDB

db = TurbojetDB()
table = db.create_table()

#debug	Thrust	Flow	Tt0		Pt0		dotm	Tt3		Pt3		Tt4		Pt4		Tt5		Pt5		P9
values = [99.9, 0.25553, 288.15, 101325.01, 0.475, 288.15, 101325, 288.15, 101325, 288.15, 101325, 101325];

db.add_measurements(values)
db.add_measurements(values)
db.add_measurements(values)
db.add_measurements(values)


