void load_img()
{
    LV_IMAGE_DECLARE(RFID_load_img);

    lv_obj_t *img_load = lv_image_create(screen_load);
    lv_image_set_src(img_load, &RFID_load_img);
    lv_obj_align(img_load, LV_ALIGN_CENTER, 0, 0);
}
