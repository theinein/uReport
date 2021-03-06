"use strict";
/**
 * Adds a button that toggles the classes on the panelContainer
 * The Layout css should have styles for all this.
 * See: twoColumn_300-a.css
 */
jQuery(function ($) {
    $('#left').prepend('<button class="fa fa-angle-left" id="slideButton"><span class="hidden-label">Slide</span></button>');
    $('#slideButton').on('click', function () {
        $('#panel-container').toggleClass('hideLeft');
    });
});
