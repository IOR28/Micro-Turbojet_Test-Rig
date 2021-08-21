import os, sys, csv, xlsxwriter
from database import TurbojetDB

def export_CSV(name_table, name_file, timestamp=True):
	header, table = TurbojetDB(name_table).fetch_table()

	#create the path
	dir_path = os.path.dirname(os.path.realpath(__file__)) + "/Results/"
	#create the name of the file
	f = dir_path + name_file + "_" + name_table + ".csv"
	
	with open(f, 'w') as file: #open file
		wr = csv.writer(file) #create writer
		
		if (timestamp): #put timestamp
			dd = name_table[0:2]
			mm = name_table[2:4]
			yyyy = name_table[4:8]
			hh = name_table[8:10]
			mins = name_table[10:12]
			
			stamp = "{}:{}, {}/{}/{}".format(hh, mins, dd, mm, yyyy)
			wr.writerow([stamp])
		
		#write header
		wr.writerow(header)
		
		#write all the data
		for row in table:
			wr.writerow(row)
	
	return f

def export_XLSX(name_table, name_file, timestamp=True):
	header, table = TurbojetDB(name_table).fetch_table()
	
	#create the path
	dir_path = os.path.dirname(os.path.realpath(__file__)) + "/Results/"
	#create the name of the file
	f = dir_path + name_file + "_" + name_table + ".xlsx"
	
	with xlsxwriter.Workbook(f) as workbook:
		worksheet = workbook.add_worksheet(name_table)
		
		header_format = workbook.add_format({'bold': True, 'border': True})
		rows_format = workbook.add_format({'border': True})
		
		row_index = 0
		column_index = 0
		
		if (timestamp): #put timestamp
			dd = name_table[0:2]
			mm = name_table[2:4]
			yyyy = name_table[4:8]
			hh = name_table[8:10]
			mins = name_table[10:12]
			
			stamp = "{}:{}, {}/{}/{}".format(hh, mins, dd, mm, yyyy)
			worksheet.write(row_index, column_index, stamp, header_format)
			row_index += 1
		
		for var_name in header: #put header
			worksheet.write(row_index, column_index, var_name, header_format)
			column_index += 1
		row_index += 1
		
		for row in table:
			column_index = 0
			for val in row:
				worksheet.write(row_index, column_index, val, rows_format)
				column_index += 1
			row_index += 1
	
	return f

#check if it was executed, not imported
if __name__ == "__main__":
	if len(sys.argv) == 4:
		name_table = sys.argv[1]
		name_file = sys.argv[2]
		to_file = sys.argv[3]
		
		if to_file == "toCSV":
			csv_file = export_CSV(name_table, name_file)
			print("Exported: ", csv_file)
		
		elif to_file == "toXLSX":
			xlsx_file = export_XLSX(name_table, name_file)
			print("Exported: ", xlsx_file)
		
		elif to_file == "toBoth":
			csv_file = export_CSV(name_table, name_file)
			print("Exported: ", csv_file)
			xlsx_file = export_XLSX(name_table, name_file)
			print("Exported: ", xlsx_file)
		
		else:
			print("Wrong to_file format.")
			print("Options are: toCSV, toXLSX and toBoth.")
			print("Try Again!")

	else:
		print("Wrong input, correct format is:")
		print(">sudo python3 export_file.py table_name name_file to_file")
		print("Arguments are:")
		print("table_name: the name of the table located inside TurbojetTests DB.")
		print("name_file: the output name of the file, _table_name and format will be added.")
		print("to_file: format of the file. Options are: toCSV, toXLSX and toBoth.")
		print("Try Again!")


