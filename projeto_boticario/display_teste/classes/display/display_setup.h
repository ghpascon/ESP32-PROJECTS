void touchscreen_read(lv_indev_t *indev, lv_indev_data_t *data)
{
    int x, y, z;
    if (touchscreen.tirqTouched() && touchscreen.touched())
    {
        TS_Point p = touchscreen.getPoint();
        x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
        y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
        z = p.z;

        data->state = LV_INDEV_STATE_PRESSED;

        // Set the coordinates
        data->point.x = x - 22;
        data->point.y = y;
    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

class display_setup
{
public:
    void setup_display()
    {
        lv_init();
        touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
        touchscreen.begin(touchscreenSPI);
        touchscreen.setRotation(3);
        lv_display_t *disp;
        disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
        lv_indev_t *indev = lv_indev_create();
        lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
        lv_indev_set_read_cb(indev, touchscreen_read);
    }
};
