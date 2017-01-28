$(document).ready(function(){
    
    // initial
    $('#content').load('content/index.php');

    // handle menu clicks
    $('ul#nav a').click(function(){
        var page = $(this).attr('href');
        //alert("test");
        $('#content').load('content/' + page + '.php');        
        return false;
    });
});