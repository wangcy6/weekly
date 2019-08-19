

/**
 * Copyright 2016 Evernote Corporation. All rights reserved.
 *
 * Survey presented to users on first launch to get data about what they are interested
 * in using Evernote for.
 */
define(['require','react','lodash','resolve!i18n','stringAffixer','ToggleButtonComponent','css!focus/OnboardingSurvey/OnboardingSurveySelectorComponent'],function (require) {
  

  var React = require('react');
  var _ = require('lodash');
  var i18n = require('resolve!i18n');
  var StringAffixer = require('stringAffixer');
  var ToggleButtonComponent = require('ToggleButtonComponent');
  require('css!focus/OnboardingSurvey/OnboardingSurveySelectorComponent');

  var POINT_OF_INTEREST = {
    NOTES: 'poi.takeNotes',
    TODOS: 'poi.toDoLists',
    IDEAS: 'poi.jotIdeas',
    REMINDERS: 'poi.reminders',
    ARCHIVE: 'poi.archive',
    DOCUMENTS: 'poi.organizeDocuments',
    CLIPS: 'poi.webClip',
    PHOTOS: 'poi.photos'
  };

  var ONBOARDING_SURVEY_VARIATION_TYPE = {
    SELECTION_ICONS_V1: 'SELECTION_ICONS_V1',
    SELECTION_ICONS_V2: 'SELECTION_ICONS_V2'
  };

  var CSS_PREFIX = 'focus-OnboardingSurveySelectorComponent';
  var I18N_PREFIX = 'OnboardingSurveySelectorComponent';

  var cssPrefixed = StringAffixer.getCssPrefixer(CSS_PREFIX);
  var i18nPrefixed = StringAffixer.getI18nPrefixer(I18N_PREFIX);

  // Displays "points of interest" the user can toggle
  var OnboardingSurveySelectorComponent = React.createClass({
    displayName: 'OnboardingSurveySelectorComponent',

    propTypes: {
      onboardingSurveyVariationType: React.PropTypes.string.isRequired,
      updateSelection: React.PropTypes.func.isRequired
    },

    getInitialState: function getInitialState() {
      return {
        // Items are toggled on with toggledOnItems[item] = true. Start with all off.
        toggledOnItems: {}
      };
    },

    // Toggles a POI on/off
    toggle: function toggle(pointOfInterest) {
      var state = this.state;
      state.toggledOnItems[pointOfInterest] = !state.toggledOnItems[pointOfInterest];
      // pass array of toggled on things to the parent
      this.props.updateSelection(_.keys(_.pick(state.toggledOnItems, _.identity)));
      this.setState(state);
    },

    // Returns the internationalized string for a POI
    getToggleButtonString: function getToggleButtonString(pointOfInterest) {
      switch (pointOfInterest) {
        case POINT_OF_INTEREST.NOTES:
          return i18n.L(i18nPrefixed('takeNotes'));
        case POINT_OF_INTEREST.TODOS:
          return i18n.L(i18nPrefixed('makeTodos'));
        case POINT_OF_INTEREST.IDEAS:
          return i18n.L(i18nPrefixed('jotDownIdeas'));
        case POINT_OF_INTEREST.REMINDERS:
          return i18n.L(i18nPrefixed('setReminders'));
        case POINT_OF_INTEREST.ARCHIVE:
          return i18n.L(i18nPrefixed('archiveBills'));
        case POINT_OF_INTEREST.DOCUMENTS:
          return i18n.L(i18nPrefixed('organizeDocs'));
        case POINT_OF_INTEREST.CLIPS:
          return i18n.L(i18nPrefixed('clipArticles'));
        case POINT_OF_INTEREST.PHOTOS:
          return i18n.L(i18nPrefixed('savePhotos'));
        default:
          throw new Error('unexpected pointOfInterest ' + pointOfInterest);
      }
    },

    // Returns the css classname corresponding to a POI
    getIllustrationClassName: function getIllustrationClassName(pointOfInterest) {
      switch (pointOfInterest) {
        case POINT_OF_INTEREST.NOTES:
          return cssPrefixed('illustration-notes');
        case POINT_OF_INTEREST.TODOS:
          return cssPrefixed('illustration-todos');
        case POINT_OF_INTEREST.IDEAS:
          return cssPrefixed('illustration-ideas');
        case POINT_OF_INTEREST.REMINDERS:
          return cssPrefixed('illustration-reminders');
        case POINT_OF_INTEREST.ARCHIVE:
          return cssPrefixed('illustration-archive');
        case POINT_OF_INTEREST.DOCUMENTS:
          return cssPrefixed('illustration-documents');
        case POINT_OF_INTEREST.CLIPS:
          return cssPrefixed('illustration-clips');
        case POINT_OF_INTEREST.PHOTOS:
          return cssPrefixed('illustration-photos');
        default:
          throw new Error('unexpected pointOfInterest ' + pointOfInterest);
      }
    },

    // Returns a POI toggle element with text-only style
    getTextOnlyToggleEl: function getTextOnlyToggleEl(pointOfInterest) {
      return React.createElement(
        ToggleButtonComponent,
        {
          btnClassName: cssPrefixed('btn-text-only'),
          btnClassNameOn: cssPrefixed('btn-text-only-on'),
          onToggle: _.partial(this.toggle, pointOfInterest),
          isToggledOn: !!this.state.toggledOnItems[pointOfInterest]
        },
        this.getToggleButtonString(pointOfInterest)
      );
    },

    // Returns a POI toggle element with illustration and checkmark styling
    getIllustratedToggleEl: function getIllustratedToggleEl(pointOfInterest) {
      var isGrayCheckVisisble = this.props.onboardingSurveyVariationType !== ONBOARDING_SURVEY_VARIATION_TYPE.SELECTION_ICONS_V1;
      return React.createElement(
        ToggleButtonComponent,
        {
          btnClassName: cssPrefixed('btn-text-illustrated', this.getIllustrationClassName(pointOfInterest)),
          btnClassNameOn: cssPrefixed('btn-text-illustrated-on'),
          onToggle: _.partial(this.toggle, pointOfInterest),
          isToggledOn: !!this.state.toggledOnItems[pointOfInterest]
        },
        this.getToggleButtonString(pointOfInterest),
        isGrayCheckVisisble && React.createElement('span', { className: cssPrefixed('checkmark', 'checkmark-ghosted') }),
        React.createElement('span', { className: cssPrefixed('checkmark') })
      );
    },

    render: function render() {
      return React.createElement(
        'div',
        { className: cssPrefixed('selector-container-high') },
        React.createElement(
          'div',
          null,
          this.getIllustratedToggleEl(POINT_OF_INTEREST.NOTES),
          this.getIllustratedToggleEl(POINT_OF_INTEREST.TODOS),
          this.getIllustratedToggleEl(POINT_OF_INTEREST.IDEAS),
          this.getIllustratedToggleEl(POINT_OF_INTEREST.DOCUMENTS)
        ),
        React.createElement(
          'div',
          null,
          this.getIllustratedToggleEl(POINT_OF_INTEREST.REMINDERS),
          this.getIllustratedToggleEl(POINT_OF_INTEREST.ARCHIVE),
          this.getIllustratedToggleEl(POINT_OF_INTEREST.CLIPS),
          this.getIllustratedToggleEl(POINT_OF_INTEREST.PHOTOS)
        )
      );
    }
  });

  return OnboardingSurveySelectorComponent;
});