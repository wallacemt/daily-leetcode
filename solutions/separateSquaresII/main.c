typedef long long ll;

typedef struct {
    ll y;
    int event_type;
    ll x_left;
    ll x_right;
} Event;

typedef struct {
    ll x_left;
    ll x_right;
} Interval;

typedef struct {
    ll start_y;
    ll height;
    ll width;
} Slice;

static int cmpEvent(const void* a, const void* b) {
    const Event* ea = (const Event*)a;
    const Event* eb = (const Event*)b;
    
    ll diff_y = ea->y - eb->y;
    if (diff_y != 0) return (diff_y > 0) ? 1 : -1;
    
    int diff_type = ea->event_type - eb->event_type;
    if (diff_type != 0) return diff_type;
    
    ll diff_left = ea->x_left - eb->x_left;
    if (diff_left != 0) return (diff_left > 0) ? 1 : -1;
    
    ll diff_right = ea->x_right - eb->x_right;
    return (diff_right > 0) ? 1 : (diff_right < 0) ? -1 : 0;
}

static int cmpInterval(const void* a, const void* b) {
    const Interval* ia = (const Interval*)a;
    const Interval* ib = (const Interval*)b;
    
    ll diff_left = ia->x_left - ib->x_left;
    if (diff_left != 0) return (diff_left > 0) ? 1 : -1;
    
    ll diff_right = ia->x_right - ib->x_right;
    return (diff_right > 0) ? 1 : (diff_right < 0) ? -1 : 0;
}

static ll union_width(const Interval* intervals, int intervalsSize) {
    if (intervalsSize == 0) return 0;
    
    Interval* sorted = (Interval*)malloc(sizeof(Interval) * intervalsSize);
    memcpy(sorted, intervals, sizeof(Interval) * intervalsSize);
    
    qsort(sorted, intervalsSize, sizeof(Interval), cmpInterval);

    ll total_width = 0;
    ll rightmost = (ll)-1e18;

    for (int i = 0; i < intervalsSize; i++) {
        ll left = sorted[i].x_left;
        ll right = sorted[i].x_right;
        
        if (left > rightmost) {
            total_width += right - left;
            rightmost = right;
        } else if (right > rightmost) {
            total_width += right - rightmost;
            rightmost = right;
        }
    }
    
    free(sorted);
    return total_width;
}

double separateSquares(int** squares, int squaresSize, int* squaresColSize) {
    (void)squaresColSize;

    if (squaresSize == 0) return 0.0;

    Event* events = (Event*)malloc(sizeof(Event) * 2 * squaresSize);
    Interval* active_intervals = (Interval*)malloc(sizeof(Interval) * 2 * squaresSize);
    Slice* horizontal_slices = (Slice*)malloc(sizeof(Slice) * 2 * squaresSize);
    
    int eventsSize = 0;
    int activeSize = 0;
    int slicesSize = 0;

    for (int i = 0; i < squaresSize; i++) {
        ll x = squares[i][0];
        ll y = squares[i][1];
        ll length = squares[i][2];
        
        events[eventsSize++] = (Event){y, 1, x, x + length};
        events[eventsSize++] = (Event){y + length, -1, x, x + length};
    }

    qsort(events, eventsSize, sizeof(Event), cmpEvent);

    double total_area = 0.0;  
    ll prev_y = events[0].y;

    for (int i = 0; i < eventsSize; i++) {
        ll y = events[i].y;
        int event_type = events[i].event_type;
        ll x_left = events[i].x_left;
        ll x_right = events[i].x_right;

        if (y > prev_y && activeSize > 0) {
            ll height = y - prev_y;
            ll width = union_width(active_intervals, activeSize);

            horizontal_slices[slicesSize++] = (Slice){prev_y, height, width};
            total_area += (double)height * (double)width;
        }

        if (event_type == 1) {
            active_intervals[activeSize++] = (Interval){x_left, x_right};
        } else {
            for (int k = 0; k < activeSize; k++) {
                if (active_intervals[k].x_left == x_left && 
                    active_intervals[k].x_right == x_right) {
                    active_intervals[k] = active_intervals[--activeSize];
                    break;
                }
            }
        }

        prev_y = y;
    }

    double half = total_area / 2.0;
    double accumulated = 0.0;

    for (int i = 0; i < slicesSize; i++) {
        ll start_y = horizontal_slices[i].start_y;
        ll height = horizontal_slices[i].height;
        ll width = horizontal_slices[i].width;

        double slice_area = (double)height * (double)width;
        
        if (accumulated + slice_area >= half) {
            double ans = (double)start_y + (half - accumulated) / (double)width;
            
            free(events);
            free(active_intervals);
            free(horizontal_slices);
            return ans;
        }
        
        accumulated += slice_area;
    }

    double ret = (double)prev_y;
    free(events);
    free(active_intervals);
    free(horizontal_slices);
    return ret;
}