$(document).ready(function () {
    let count = 0;
    let dist;
    let threshold_low;
    let threshold_high;
    let indicator = 0;

    if (pk == 1) {
        threshold_low = 90
        threshold_high = 150
    } else {
        threshold_low = 90
        threshold_high = 150
    }

    let update = setInterval(() => {

        setTimeout(()=>{
            $.ajax({
                url:get_distance,
                success: function (data) {
                    dist = data.distance
                }
            })

            if(dist > threshold_high){
                if(indicator){
                      count += 1;
                      indicator = 0;
                }
            }
            if(dist < threshold_low){
                indicator = 1;
            }
            console.log(dist)
            $('#count').text(`${count}`)
        }, 50)
    },100)

     $(document).on('click', '#stop_btn', function () {
        alert(`멈췄습니다! 총 ${count}개`);
        clearInterval(update);
    });
})