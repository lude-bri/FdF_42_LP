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

fs cmd
break read_map
run maps/test_maps/mars.fdf
main
