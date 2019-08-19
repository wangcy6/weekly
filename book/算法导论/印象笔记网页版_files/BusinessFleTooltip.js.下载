/**
 * Copyright 2015-2017 Evernote Corporation. All rights reserved.
 */
define(['require','lodash','react','focusFleTooltip','enPropTypes'],function(require) {
  

  var _ = require('lodash');
  var React = require('react');
  var FleTooltip = require('focusFleTooltip');
  var EnPropTypes = require('enPropTypes');

  /**
   * The different kinds of business FLE tooltips. Note that these names are referenced in
   * BusinessFirstLaunchView.java in webclient.
   */
  var Tooltips = {
    NOTEBOOKS_DRAWER: {
      subheadingKey: 'Focus.tooltip.FleTooltip.business.notebooksDrawer.subheading',
      textKey: 'Focus.tooltip.FleTooltip.business.notebooksDrawer.text',
      arrowPosition: FleTooltip.ArrowPosition.LEFT_MIDDLE
    },
    BUSINESS_NOTEBOOKS: {
      subheadingKey: 'Focus.tooltip.FleTooltip.business.businessNotebooks.subheading',
      textKey: 'Focus.tooltip.FleTooltip.business.businessNotebooks.text',
      arrowPosition: FleTooltip.ArrowPosition.TOP_LEFT
    },
    PERSONAL_NOTEBOOKS: {
      subheadingKey: 'Focus.tooltip.FleTooltip.business.personalNotebooks.subheading',
      textKey: 'Focus.tooltip.FleTooltip.business.personalNotebooks.text',
      arrowPosition: FleTooltip.ArrowPosition.TOP_LEFT
    },
    ALL_BUSINESS_NOTEBOOKS_1: {
      subheadingKey: 'Focus.tooltip.FleTooltip.business.allBusinessNotebooks1.subheading',
      textKey: 'Focus.tooltip.FleTooltip.business.allBusinessNotebooks1.text',
      arrowPosition: FleTooltip.ArrowPosition.BOTTOM_LEFT
    },
    ALL_BUSINESS_NOTEBOOKS_2_EMPTY: {
      subheadingKey: 'Focus.tooltip.FleTooltip.business.allBusinessNotebooks2Empty.subheading',
      textKey: 'Focus.tooltip.FleTooltip.business.allBusinessNotebooks2Empty.text',
      arrowPosition: FleTooltip.ArrowPosition.LEFT_MIDDLE
    },
    ALL_BUSINESS_NOTEBOOKS_2_WITH_NOTEBOOKS: {
      subheadingKey: 'Focus.tooltip.FleTooltip.business.allBusinessNotebooks2WithNotebooks.subheading',
      textKey: 'Focus.tooltip.FleTooltip.business.allBusinessNotebooks2WithNotebooks.text',
      arrowPosition: FleTooltip.ArrowPosition.LEFT_MIDDLE
    },
    ATTACH_FILES: {
      subheadingKey: 'Focus.tooltip.FleTooltip.business.attachFiles.subheading',
      textKey: 'Focus.tooltip.FleTooltip.business.attachFiles.text',
      arrowPosition: FleTooltip.ArrowPosition.TOP_RIGHT
    },
    SHARE_NOTE: {
      subheadingKey: 'Focus.tooltip.FleTooltip.business.shareNote.subheading',
      textKey: 'Focus.tooltip.FleTooltip.business.shareNote.text',
      arrowPosition: FleTooltip.ArrowPosition.TOP_RIGHT
    },
    SHARE_NOTEBOOK: {
      subheadingKey: 'Focus.tooltip.FleTooltip.business.shareNotebook.subheading',
      textKey: 'Focus.tooltip.FleTooltip.business.shareNotebook.text',
      arrowPosition: FleTooltip.ArrowPosition.LEFT_MIDDLE
    }
  };

  var BusinessFleTooltip = React.createClass({
    propTypes: {
      name: EnPropTypes.objectProperty(Tooltips).isRequired,
      xPosition: React.PropTypes.number.isRequired, // x position where the arrow points
      yPosition: React.PropTypes.number.isRequired // y position where the arrow points
    },

    render: function() {
      var props = _.cloneDeep(Tooltips[this.props.name]);
      _.extend(props, _.omit(this.props, 'name'));
      return React.createElement(FleTooltip, props);
    }
  });

  BusinessFleTooltip.Tooltips = Tooltips;

  return BusinessFleTooltip;
});
