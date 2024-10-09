set trace-commands on
set logging enabled on
set print pretty on
set print array on

define read_map
	disp x
	disp y
	disp map->coord[y]
	disp line
end

define fill_mtrx
	disp data[c]
	disp c
end

fs cmd
break read_map
run 4x4_2.fdf
main
