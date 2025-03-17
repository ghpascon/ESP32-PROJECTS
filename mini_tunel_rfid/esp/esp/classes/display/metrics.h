class metrics
{
public:
    void draw_metrics()
    {
        static const uint16_t metrics_graph_vp = 1000;

        static const int offset = 5;

        static const int colors[] = {
            0,
            2016,
            63488,
            52825,
            65535};

        int dimensions[] = {
            570,
            5,
            700,
            245};

            if(client == 1)
            {
                dimensions[0] = 320;
                dimensions[1] = 5;
                dimensions[2] = 420;
                dimensions[3] = 135;
            }

        const int results_cnt = results_qtd;

        int total_boxes = 0;
        for (int y = 0; y < results_cnt; y++)
            total_boxes += box_results[y];

        int box_results_val[results_cnt];
        for (int y = 0; y < results_cnt; y++)
        {
            box_results_val[y] = map(box_results[y], 0, total_boxes, 0, dimensions[3] - dimensions[1]);
        }

        // int result_dimensions[results_cnt * 4];
        // int start_height = dimensions[3];
        // for (int y = 0; y < results_cnt; y++)
        // {
        //     result_dimensions[y * 4 + 0] = dimensions[0] + offset;
        //     result_dimensions[y * 4 + 1] = start_height - box_results_val[y] + offset;
        //     result_dimensions[y * 4 + 2] = dimensions[2] - offset;
        //     result_dimensions[y * 4 + 3] = start_height - offset;
        //     start_height -= box_results_val[y];
        // }

        int result_dimensions[results_cnt * 4];
        int start_x = dimensions[0];
        for (int y = 0; y < results_cnt; y++)
        {
            result_dimensions[y * 4 + 0] = start_x + offset;
            result_dimensions[y * 4 + 1] = dimensions[3] - box_results_val[y] + offset;
            result_dimensions[y * 4 + 2] = start_x + ((dimensions[2] - dimensions[0]) / results_cnt) - offset;
            result_dimensions[y * 4 + 3] = dimensions[3] - offset;

            if ((offset - box_results_val[y]) > 0)
                result_dimensions[y * 4 + 1] = dimensions[3] - offset;

            start_x += ((dimensions[2] - dimensions[0]) / results_cnt);
        }

        uint16_t metrics_graph_val[] = {
            4,
            results_cnt * 2 + 1,

            dimensions[0],
            dimensions[1],
            dimensions[2],
            dimensions[3],
            colors[0],

            result_dimensions[0],
            result_dimensions[1],
            result_dimensions[2],
            result_dimensions[3],
            colors[result_dimensions[1] > offset ? 1 : 0],
            result_dimensions[0] - offset,
            dimensions[1],
            result_dimensions[2] + offset,
            result_dimensions[1] - offset,
            colors[4],

            result_dimensions[4],
            result_dimensions[5],
            result_dimensions[6],
            result_dimensions[7],
            colors[result_dimensions[5] > offset ? 2 : 0],
            result_dimensions[4] - offset,
            dimensions[1],
            result_dimensions[6] + offset,
            result_dimensions[5] - offset,
            colors[4],

            result_dimensions[8],
            result_dimensions[9],
            result_dimensions[10],
            result_dimensions[11],
            colors[result_dimensions[9] > offset ? 3 : 0],
            result_dimensions[8] - offset,
            dimensions[1],
            result_dimensions[10] + offset * 2,
            result_dimensions[9] - offset,
            colors[4],

        };

        display_metrics.write(
            String("CAIXAS PROCESSADAS:") +
            "\nTOTAL: " + String(total_boxes) +
            "\nAPROVADO: " + String(box_results[0]) +
            "\nREPROVADO: " + String(box_results[1]) +
            "\nTIMEOUT: " + String(box_results[2]));

        Lcm.writeVP(metrics_graph_vp, metrics_graph_val, sizeof(metrics_graph_val) / sizeof(metrics_graph_val[0]));
    }

    void clear_metrics()
    {
        Serial.println("#CLEAR_DATA");
        box_results[0] = 0;
        box_results[1] = 0;
        box_results[2] = 0;
    }

    void check_metrics()
    {
        check_results();

        static String last_metrics;
        const String current_metrics = String(box_results[0]) + String(box_results[1]) + String(box_results[2]);
        if (last_metrics == current_metrics)
            return;

        last_metrics = current_metrics;
        draw_metrics();
    }

private:
    void check_results()
    {
        if (!box_inside)
            return;
        static bool last_states[3] = {false, false, false};

        if (last_states[0] != cx_ok)
        {
            last_states[0] = cx_ok;
            if (cx_ok)
                box_results[0]++;
        }

        if (last_states[1] != cx_erro)
        {
            last_states[1] = cx_erro;
            if (cx_erro)
                box_results[1]++;
        }

        if (last_states[2] != timeout)
        {
            last_states[2] = timeout;
            if (timeout)
            {
                box_results[2]++;
                box_results[1]--;
            }
        }
    }
};
