def validate(project):

    brd4160a_is_selected = project.is_selected('brd4160a')
    brd2204a_is_selected = project.is_selected('brd2204a')
    hardware_board = project.is_provided('hardware_board')
    
    if brd4160a_is_selected == 0 and project.is_selected('micriumos_fs_storage_nor_driver_spi') == 1 and hardware_board == 1:
        project.warning('The selected board may not have NOR over SPI', project.target_for_defines("FS_STORAGE_NOR"))
        
    if brd2204a_is_selected == 0 and project.is_selected('micriumos_fs_storage_nor_driver_quad_spi') == 1 and hardware_board == 1:
        project.warning('The selected board may not have NOR over Quad SPI', project.target_for_defines("FS_STORAGE_NOR"))