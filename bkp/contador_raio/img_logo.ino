void img_logo() {
  LV_IMAGE_DECLARE(embastec);

  lv_obj_t* img_load = lv_image_create(screen_main);
  lv_image_set_src(img_load, &embastec);
  lv_obj_align(img_load, LV_ALIGN_CENTER, 0, 25 - SCREEN_HEIGHT / 2);
}
